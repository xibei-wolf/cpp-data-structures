// event_dispatcher.h
// 事件分发器（Event Dispatcher）
//
// 接口：
//   HandlerId subscribe(std::function<void(int)> handler);
//   void      unsubscribe(HandlerId id);
//   void      emit(int value);
//
// 实现要点：
//   1. 内部结构与 testvtable.cpp 中的草稿一致：std::list 保存条目以维持订阅顺序，
//      std::unordered_map<HandlerId, list::iterator> 做 id -> 条目的索引，
//      使得 unsubscribe 是 O(1)。
//   2. 线程安全：所有对 entries_ / index_ 的读写都由 mtx_ 保护。
//   3. emit 期间不持锁：先在锁内对订阅表做快照，释放锁后再回调用户代码。
//      因此回调内部再次 subscribe / unsubscribe / emit 都不会死锁（支持重入）。
//   4. 派发过程中的退订立即生效：若某个回调在 emit 期间退掉了尚未被调用的另一个回调，
//      后者在本次 emit 中不会再被调用。
//   5. 异常隔离：某个回调抛异常不会影响后续回调，异常交给可选的错误处理器。
//
// 典型用法：
//   EventDispatcher dispatcher;
//   HandlerId id = dispatcher.subscribe([](int v){ std::cout << v << '\n'; });
//   dispatcher.emit(42);
//   dispatcher.unsubscribe(id);

#ifndef EVENT_DISPATCHER_H_
#define EVENT_DISPATCHER_H_

#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

// 订阅句柄：由 subscribe 返回，用于 unsubscribe。
using HandlerId = std::uint64_t;

// 非法句柄：subscribe 传入空 function 时返回。
constexpr HandlerId kInvalidHandlerId = 0;

class EventDispatcher {
public:
    using HandlerId = ::HandlerId;
    // 回调抛出异常时，异常被捕获后交给该处理器（可选）。
    using ErrorHandler = std::function<void(std::exception_ptr)>;

    EventDispatcher() = default;
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;

    // 注册一个事件处理器，返回唯一句柄。
    // 若传入空的 function，返回 kInvalidHandlerId 且不注册任何东西。
    HandlerId subscribe(std::function<void(int)> handler) {
        if (!handler) {
            return kInvalidHandlerId;
        }
        std::lock_guard<std::mutex> lock(mtx_);
        const HandlerId id = nextId_++;
        entries_.push_back(Entry{id, std::move(handler)});
        index_[id] = std::prev(entries_.end());
        return id;
    }

    // 取消订阅。句柄不存在时是安全的空操作。
    void unsubscribe(HandlerId id) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = index_.find(id);
        if (it == index_.end()) {
            return;
        }
        entries_.erase(it->second);
        index_.erase(it);
    }

    // 派发事件：按订阅顺序调用所有仍然有效的处理器。
    void emit(int value) {
        std::vector<std::pair<HandlerId, std::function<void(int)>>> snapshot;
        {
            std::lock_guard<std::mutex> lock(mtx_);
            snapshot.reserve(entries_.size());
            for (const Entry& entry : entries_) {
                snapshot.emplace_back(entry.id, entry.handler);
            }
        }

        // 注意：此时已释放锁，回调里可以自由地 subscribe / unsubscribe / emit。
        for (const auto& item : snapshot) {
            // 快照之后、真正调用之前，该回调可能已被退订，此时跳过。
            if (!isSubscribed(item.first)) {
                continue;
            }
            try {
                item.second(value);
            } catch (...) {
                dispatchError(std::current_exception());
            }
        }
    }

    // 当前有效订阅数。
    std::size_t handlerCount() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return entries_.size();
    }

    // 判断某个句柄是否仍然有效。
    bool contains(HandlerId id) const {
        std::lock_guard<std::mutex> lock(mtx_);
        return index_.find(id) != index_.end();
    }

    // 一次性清空所有订阅。
    void clear() {
        std::lock_guard<std::mutex> lock(mtx_);
        entries_.clear();
        index_.clear();
    }

    // 设置异常处理器；不设置时异常信息打印到 stderr。
    void setErrorHandler(ErrorHandler onError) {
        std::lock_guard<std::mutex> lock(mtx_);
        errorHandler_ = std::move(onError);
    }

private:
    struct Entry {
        HandlerId id;
        std::function<void(int)> handler;
    };

    bool isSubscribed(HandlerId id) const {
        std::lock_guard<std::mutex> lock(mtx_);
        return index_.find(id) != index_.end();
    }

    void dispatchError(std::exception_ptr eptr) {
        ErrorHandler handler;
        {
            std::lock_guard<std::mutex> lock(mtx_);
            handler = errorHandler_;
        }
        if (handler) {
            try {
                handler(eptr);
            } catch (...) {
                // 错误处理器自身再抛异常，忽略，避免递归。
            }
        } else {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                std::cerr << "[EventDispatcher] handler threw: " << ex.what() << '\n';
            } catch (...) {
                std::cerr << "[EventDispatcher] handler threw unknown exception\n";
            }
        }
    }

private:
    mutable std::mutex mtx_;
    // list 保证遍历顺序 == 订阅顺序
    std::list<Entry> entries_;
    // id -> 条目位置，unsubscribe 为 O(1)
    std::unordered_map<HandlerId, std::list<Entry>::iterator> index_;
    HandlerId nextId_ = 1;  // 0 保留给 kInvalidHandlerId
    ErrorHandler errorHandler_;
};

#endif  // EVENT_DISPATCHER_H_
