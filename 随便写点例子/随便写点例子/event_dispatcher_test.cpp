// event_dispatcher_test.cpp
// EventDispatcher 的测试用例 + 主函数
//
// 用例覆盖：
//   1. 基本订阅与派发
//   2. 多处理器的调用顺序（按订阅顺序）
//   3. 退订后不再被调用；退订非法句柄不崩溃
//   4. emit 过程中退订另一个处理器 -> 本次 emit 不再调用它
//   5. emit 过程中新增订阅 -> 本次 emit 不调用，下一次 emit 才调用
//   6. 处理器抛异常 -> 不影响其它处理器，异常交给错误处理器
//   7. 传入空 std::function -> 返回 kInvalidHandlerId 且不注册
//   8. 处理器内部重入 emit -> 不死锁
//   9. handlerCount / contains / clear
//   10. 多线程并发订阅/退订/派发 -> 无数据竞争、无崩溃、计数正确

#include "event_dispatcher.h"

#include <atomic>
#include <chrono>
#include <exception>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace {

// ---------------------------------------------------------------------------
// 迷你测试框架
// ---------------------------------------------------------------------------
int g_checks = 0;
int g_failed = 0;
std::string g_currentCase;

void beginCase(const std::string& name) {
    g_currentCase = name;
    std::cout << "\n[ CASE ] " << name << '\n';
}

void check(bool ok, const std::string& expr, int line) {
    ++g_checks;
    std::cout << (ok ? "   [ OK ] " : "   [FAIL] ") << expr;
    if (!ok) {
        ++g_failed;
        std::cout << "   <== line " << line << " in " << g_currentCase;
    }
    std::cout << '\n';
}

#define CHECK(expr) check((expr), #expr, __LINE__)

void section(const std::string& title) {
    std::cout << "  -- " << title << '\n';
}

// ---------------------------------------------------------------------------
// 1. 基本订阅与派发
// ---------------------------------------------------------------------------
void testBasicSubscribeEmit() {
    beginCase("基本订阅与派发");
    EventDispatcher dispatcher;

    std::vector<int> received;
    HandlerId id = dispatcher.subscribe([&received](int v) { received.push_back(v); });

    CHECK(id != kInvalidHandlerId);
    CHECK(dispatcher.handlerCount() == 1);

    dispatcher.emit(7);
    dispatcher.emit(9);

    CHECK(received.size() == 2);
    CHECK(received.size() == 2 && received[0] == 7);
    CHECK(received.size() == 2 && received[1] == 9);
}

// ---------------------------------------------------------------------------
// 2. 多处理器按订阅顺序调用
// ---------------------------------------------------------------------------
void testOrderIsSubscriptionOrder() {
    beginCase("多处理器按订阅顺序调用");
    EventDispatcher dispatcher;
    std::vector<std::string> order;

    dispatcher.subscribe([&order](int) { order.push_back("A"); });
    dispatcher.subscribe([&order](int) { order.push_back("B"); });
    dispatcher.subscribe([&order](int) { order.push_back("C"); });

    dispatcher.emit(1);

    CHECK(order.size() == 3);
    CHECK(order.size() == 3 && order[0] == "A");
    CHECK(order.size() == 3 && order[1] == "B");
    CHECK(order.size() == 3 && order[2] == "C");
}

// ---------------------------------------------------------------------------
// 3. 退订
// ---------------------------------------------------------------------------
void testUnsubscribe() {
    beginCase("退订");
    EventDispatcher dispatcher;
    int a = 0, b = 0;

    HandlerId idA = dispatcher.subscribe([&a](int) { ++a; });
    dispatcher.subscribe([&b](int) { ++b; });

    dispatcher.emit(0);
    CHECK(a == 1);
    CHECK(b == 1);

    section("退订 A");
    dispatcher.unsubscribe(idA);
    CHECK(dispatcher.handlerCount() == 1);
    CHECK(!dispatcher.contains(idA));

    dispatcher.emit(0);
    CHECK(a == 1);  // A 不再被调用
    CHECK(b == 2);  // B 继续被调用

    section("退订一个不存在的句柄（不应崩溃）");
    dispatcher.unsubscribe(999999);
    dispatcher.unsubscribe(kInvalidHandlerId);
    CHECK(dispatcher.handlerCount() == 1);
}

// ---------------------------------------------------------------------------
// 4. emit 过程中退订另一个处理器
// ---------------------------------------------------------------------------
void testUnsubscribeDuringEmit() {
    beginCase("emit 过程中退订另一个处理器");
    EventDispatcher dispatcher;
    bool calledA = false, calledB = false;
    HandlerId idB = 0;

    dispatcher.subscribe([&](int) {
        calledA = true;
        dispatcher.unsubscribe(idB);  // A 在 B 之前被调用，退掉 B
    });
    idB = dispatcher.subscribe([&calledB](int) { calledB = true; });

    dispatcher.emit(0);

    CHECK(calledA);
    CHECK(!calledB);  // B 在本次 emit 中被跳过
    CHECK(dispatcher.handlerCount() == 1);

    section("下一次 emit 时 B 早已不存在");
    dispatcher.emit(0);
    CHECK(!calledB);
}

// ---------------------------------------------------------------------------
// 5. emit 过程中新增订阅
// ---------------------------------------------------------------------------
void testSubscribeDuringEmit() {
    beginCase("emit 过程中新增订阅");
    EventDispatcher dispatcher;
    bool calledNew = false;

    dispatcher.subscribe([&](int) {
        dispatcher.subscribe([&calledNew](int) { calledNew = true; });
    });

    dispatcher.emit(0);
    CHECK(!calledNew);  // 本次 emit 的快照里没有它

    section("下一次 emit 才调用新订阅者");
    dispatcher.emit(0);
    CHECK(calledNew);
}

// ---------------------------------------------------------------------------
// 6. 处理器抛异常
// ---------------------------------------------------------------------------
void testExceptionIsolation() {
    beginCase("处理器抛异常");
    EventDispatcher dispatcher;
    bool afterCalled = false;
    int errorCount = 0;

    dispatcher.setErrorHandler([&errorCount](std::exception_ptr eptr) {
        ++errorCount;
        try {
            std::rethrow_exception(eptr);
        } catch (const std::exception& ex) {
            std::cout << "        caught by error handler: " << ex.what() << '\n';
        }
    });

    dispatcher.subscribe([](int) { throw std::runtime_error("boom"); });
    dispatcher.subscribe([&afterCalled](int) { afterCalled = true; });

    dispatcher.emit(0);

    CHECK(afterCalled);     // 前面的异常没有阻断后面的处理器
    CHECK(errorCount == 1); // 异常被交给错误处理器
}

// ---------------------------------------------------------------------------
// 7. 空 function
// ---------------------------------------------------------------------------
void testEmptyHandler() {
    beginCase("传入空 std::function");
    EventDispatcher dispatcher;
    std::function<void(int)> empty;

    HandlerId id = dispatcher.subscribe(empty);
    CHECK(id == kInvalidHandlerId);
    CHECK(dispatcher.handlerCount() == 0);

    dispatcher.emit(1);  // 没有订阅者，派发不应崩溃
    CHECK(true);
}

// ---------------------------------------------------------------------------
// 8. 重入 emit
// ---------------------------------------------------------------------------
void testReentrantEmit() {
    beginCase("处理器内部重入 emit");
    EventDispatcher dispatcher;
    int inner = 0, outer = 0;
    int depth = 0;

    dispatcher.subscribe([&](int v) {
        ++outer;
        if (depth == 0) {
            ++depth;
            dispatcher.emit(v + 1);  // 重入，不应该死锁
        }
    });
    dispatcher.subscribe([&inner](int) { ++inner; });

    dispatcher.emit(1);

    CHECK(outer == 2);  // 外层 1 次 + 重入 1 次
    CHECK(inner == 2);  // 两个订阅者都被外层和内层各调一次
}

// ---------------------------------------------------------------------------
// 9. handlerCount / contains / clear
// ---------------------------------------------------------------------------
void testCountContainsClear() {
    beginCase("handlerCount / contains / clear");
    EventDispatcher dispatcher;

    HandlerId id1 = dispatcher.subscribe([](int) {});
    HandlerId id2 = dispatcher.subscribe([](int) {});

    CHECK(dispatcher.handlerCount() == 2);
    CHECK(dispatcher.contains(id1));
    CHECK(dispatcher.contains(id2));

    dispatcher.clear();
    CHECK(dispatcher.handlerCount() == 0);
    CHECK(!dispatcher.contains(id1));
}

// ---------------------------------------------------------------------------
// 10. 多线程并发
// ---------------------------------------------------------------------------
void testThreadSafety() {
    beginCase("多线程并发订阅/退订/派发");
    EventDispatcher dispatcher;
    std::atomic<int> callCount{0};
    std::atomic<int> liveCount{0};

    constexpr int kThreads = 8;
    constexpr int kPerThread = 200;

    std::vector<std::thread> workers;
    workers.reserve(kThreads);

    for (int t = 0; t < kThreads; ++t) {
        workers.emplace_back([&dispatcher, &callCount, &liveCount, kPerThread]() {
            for (int i = 0; i < kPerThread; ++i) {
                HandlerId id = dispatcher.subscribe([&callCount](int) { callCount.fetch_add(1); });
                liveCount.fetch_add(1);
                dispatcher.emit(i);
                dispatcher.unsubscribe(id);
                liveCount.fetch_sub(1);
            }
        });
    }

    // 再起一个线程只做纯派发，最大化竞争
    std::thread emitter([&dispatcher, kPerThread]() {
        for (int i = 0; i < kPerThread * 4; ++i) {
            dispatcher.emit(i);
        }
    });

    for (auto& w : workers) {
        w.join();
    }
    emitter.join();

    CHECK(dispatcher.handlerCount() == 0);   // 全部退订干净
    CHECK(liveCount.load() == 0);
    CHECK(callCount.load() > 0);              // 回调确实被执行过
    std::cout << "        total callback invocations: " << callCount.load() << '\n';
}

// ---------------------------------------------------------------------------
// 演示：贴近真实场景的用法
// ---------------------------------------------------------------------------
void demoUsage() {
    beginCase("用法演示");
    EventDispatcher dispatcher;

    HandlerId loggerId = dispatcher.subscribe([](int v) {
        std::cout << "        [logger] value = " << v << '\n';
    });
    dispatcher.subscribe([](int v) {
        std::cout << "        [sum]    2 * value = " << 2 * v << '\n';
    });

    dispatcher.emit(21);

    section("退掉 logger 后再派发");
    dispatcher.unsubscribe(loggerId);
    dispatcher.emit(21);
}

}  // namespace

int main() {
    std::cout << "==================== EventDispatcher 测试 ====================\n";

    testBasicSubscribeEmit();
    testOrderIsSubscriptionOrder();
    testUnsubscribe();
    testUnsubscribeDuringEmit();
    testSubscribeDuringEmit();
    testExceptionIsolation();
    testEmptyHandler();
    testReentrantEmit();
    testCountContainsClear();
    testThreadSafety();
    demoUsage();

    std::cout << "\n==================== 结果汇总 ====================\n";
    std::cout << "checks  : " << g_checks << '\n';
    std::cout << "failed  : " << g_failed << '\n';
    std::cout << (g_failed == 0 ? "ALL TESTS PASSED\n" : "SOME TESTS FAILED\n");
    return g_failed == 0 ? 0 : 1;
}
