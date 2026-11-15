#include<iostream>
//
using namespace std; 
#include <vector>
#include <string>
#include <cstdio>
#include <memory>
#include <list>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <utility>
#include <unordered_map>
#include <sstream>
#include <map>
#include <algorithm>
#include <cstdint>



//class EventDispatcher {
//public:
//    HandlerId subscribe(std::function<void(int)> handler);
//    void unsubscribe(HandlerId id);
//    void emit(int value);
//
//private:
//    struct Entry { HandlerId id; std::function<void(int)> handler; };
//    mutable std::mutex mtx_;
//    std::list<Entry> entries_;
//    std::unordered_map<HandlerId, std::list<Entry>::iterator> index_;
//    HandlerId nextId_ = 1;
//
//};
//
// 上面这个骨架已经实现好了，见同目录下的 event_dispatcher.h
// （内部结构与草稿一致：list 保序 + unordered_map 做 O(1) 退订；
//   额外做了线程安全、emit 快照、异常隔离）。
// 完整实现 + 测试用例 + main 在 event_dispatcher_test.cpp，直接运行即可。



//int main() {
//	string test = "a bbbb cbbb d d d d e e f ";
//	stringstream ss(test);
//	string word;
//	map<string, int> m;
//	while (ss >> word) {
//		m[word]++;
//	}
//
//	vector<pair<string, int>> vecs(m.begin(), m.end());
//	sort(vecs.begin(), vecs.end(), [](const pair<string, int>& a, const pair<string, int>& b) {if (a.second != b.second) return a.second > b.second; else return a.first < b.first; });
//
//	for (auto& vec : vecs) {
//		cout << vec.first << " : " << vec.second << endl;
//	}
//
//	return 0;
//}






//��Ҫ�������һ�㱾�ػ��棬���� RPC ���ε��û����á�Ҫ��
//
//�� �������� cap������ʱ�� LRU ��̭��
//�� ÿ�� key �� TTL�����ڼ����ɼ���
//�� ���̶߳�д��
//�� ��¶ ������ / ��̭������ָ�ꣻ
//�� ��̭ / ����ʱ�����ص����ͷŹ�����Դ����㣩��
//�� ���� value ������ֵ���� 1MB��ʱ�����棬ֱ�ӻ�Դ��
//Ҫ��д�����ݽṹѡ�� + ����ʵ�֣����ش���̭�ص�Ϊʲô�����ڳ���ʱִ�У�

//class LRUCache
//{
//public:
//	LRUCache(int capacity):cap(capacity){}
//	int Get(int key) {
//		auto it = map.find(key);
//		if (it == map.end()) {
//			return -1;
//		}
//		else {
//			cache_lst.splice(cache_lst.begin(), cache_lst, it->second);
//		}
//		return it->second->second;
//	}
//	void Put(int key,int value) {
//		auto it = map.find(key);
//		if (it != map.end()) {
//			it->second->second = value;
//			cache_lst.splice(cache_lst.begin(), cache_lst,it->second);
//			return;
//		}
//	
//			if (cache_lst.size() == cap) {
//				int backkey = cache_lst.back().first;
//				map.erase(backkey);
//				cache_lst.pop_back();
//			}
//		cache_lst.emplace_front(std::make_pair(key, value));
//		map[key] = cache_lst.begin();
//	}
//	~LRUCache() {
//
//	}
//
//private:
//	int cap;
//	std::list<std::pair<int, int>> cache_lst;
//	std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;
//};




//
//class A {
//public:
//    virtual void fa() {}
//    int a = 1;
//};
//
//class B : virtual public A {
//public:
//    virtual void fb() {}
//    int b = 2;
//};
//
//class C : virtual public A {
//public:
//    virtual void fc() {}
//    int c = 3;
//};
//
//class D : public B, public C {
//public:
//    int d = 4;
//};
//
//int main() {
//    B b;
//    C c;
//    D d;
//
//    cout << sizeof(A) << endl;
//    cout << sizeof(B) << endl;
//    cout << sizeof(C) << endl;
//    cout<<sizeof(D) << endl;
//
//    system("pause");
//    return 0;
//}


///d1 reportAllClassLayout 