/*
146


基本思想

S1

维护一个Map和一个list
Map的key为输入的key，value为List里面元素的指针
List元素含有key value

每当有put操作的时候，从Map中查询是否存在key，存在的话拿到元素指针，修改元素value，将元素取出放在list的头部
不存在的话，检查是否满cache，如果满了，就将尾部丢掉，将Map中对应key找到并且丢掉
然后在头部放入新元素，在Map中保存key和元素指针

get操作，从Map中拿到元素指针，返回元素的值，并且将元素放入头部
 
TLE

*/

#include <unordered_map>
#include <list>
using namespace std;


class LRUCache {

unordered_map<int, list<pair<int, int>>::iterator> cache;
list<pair<int, int>> priority_que;
int cap;

public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if(cache.find(key) != cache.end()){
            list<pair<int, int>>::iterator elem = cache[key];
            pair<int, int> cur_p = *elem;
            if(elem != priority_que.begin()){
                priority_que.erase(elem);
                cache[key] = priority_que.insert(priority_que.begin(), cur_p);
            }
            return cur_p.second;
        }
        else{
            return -1;
        }
    }
    
    void put(int key, int value){
        if(cache.find(key) == cache.end()){
            cache[key] = priority_que.insert(priority_que.begin(), pair<int, int>(key, value));
            if(priority_que.size() > cap){
                pair<int, int> to_del = priority_que.back();
                priority_que.pop_back();
                cache.erase(to_del.first);
            }
        }
        else{
            list<pair<int, int>>::iterator elem = cache[key];
            priority_que.erase(elem);
            cache[key] = priority_que.insert(priority_que.begin(), pair<int, int>(key, value));
        }
    }
};