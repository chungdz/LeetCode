/*
146

LRU缓存机制
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。

获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果密钥已经存在，则变更其数据值；如果密钥不存在，则插入该组「密钥/数据值」。
当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

 

进阶:

你是否可以在 O(1) 时间复杂度内完成这两种操作？

示例:

LRUCache cache = new LRUCache(2);

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       返回  1
cache.put(3, 3);    该操作会使得密钥 2 作废
cache.get(2);       返回 -1 (未找到)
cache.put(4, 4);    该操作会使得密钥 1 作废
cache.get(1);       返回 -1 (未找到)
cache.get(3);       返回  3
cache.get(4);       返回  4
*/

#include <unordered_map>
using namespace std;

/*
 解法一：

 维护一个Map和一个List
 Map的key为输入的key，value为List里面元素的指针
 List元素含有key value

 每当有put操作的时候，从Map中查询是否存在key，存在的话拿到元素指针，修改元素value，将元素取出放在list的头部
 不存在的话，检查是否满cache，如果满了，就将尾部丢掉，将Map中对应key找到并且丢掉
 然后在头部放入新元素，在Map中保存key和元素指针

 get操作，从Map中拿到元素指针，返回元素的值，并且将元素放入头部

TLE

 */
class Node {
public:
    int key;
    int val;
    Node* next;
    Node* previous;
    
    Node(int _key, int _val) {
        key = _key;
        val = _val;
        next = NULL;
        previous = NULL;
    }
};

class MyList {
public:
    Node* root;
    Node* tail;
    MyList(){
        root = new Node(NULL, NULL);
        tail = new Node(NULL, NULL);
        root->next = tail;
        tail->previous = root;
    }
    void push_front(Node* to_insert){
        to_insert->next = root->next;
        root->next->previous = to_insert;

        to_insert->previous = root;
        root->next = to_insert;

        return;
    }
    int back_key(){
        Node* last_node = tail->previous;
        if(last_node == root){
            return NULL;
        }
        return last_node->key;
    }
    void pop_back(){
        Node* to_del = tail->previous;
        if(to_del == root){
            return;
        }
        to_del->previous->next = tail;
        tail->previous = to_del->previous;

        delete to_del;
        return;
    }
    void pop_node(Node* to_pop){
        if(to_pop == root || to_pop == tail){
            return;
        }
        to_pop->previous->next = to_pop->next;
        to_pop->next->previous = to_pop->previous;

        to_pop->previous = NULL;
        to_pop->next = NULL;
        return;
    }
};

class LRUCache {

unordered_map<int, Node*>* list_pos;
MyList* value_list;
int cap;

public:
    LRUCache(int capacity) {
        list_pos = new unordered_map<int, Node*>();
        value_list = new MyList();
        cap = capacity;
    }
    
    int get(int key) {
        Node* get_node;
        //find the key exist
        if(list_pos->find(key) != list_pos->end()){
            get_node = (*list_pos)[key];
            int result = get_node->val;
            value_list->pop_node(get_node);
            value_list->push_front(get_node);
            return result;
        }
        else{
            return -1;
        }
    }
    
    void put(int key, int value) {
        Node* put_node;
        //find the key exist
        if(list_pos->find(key) != list_pos->end()){
            put_node = (*list_pos)[key];
            put_node->val = value;
            value_list->pop_node(put_node);
            value_list->push_front(put_node);
        }
        else{
            //whether to del
            while(list_pos->size() >= cap){
                int to_del_key = value_list->back_key();
                value_list->pop_back();
                list_pos->erase(to_del_key);
            }
            put_node = new Node(key, value);
            value_list->push_front(put_node);
            (*list_pos)[key] = put_node;
        }
    }
};