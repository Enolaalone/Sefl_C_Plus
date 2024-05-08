#include<iostream>
#include<string>
#include<cstdbool>
#include<stack>
#include<vector>
#include<map>
#include <algorithm>
#include <queue>
#include<unordered_set>
#include<unordered_map>
using namespace std;

struct DLinkedNode
{
    int key, value;//键值对

    DLinkedNode* pre;
    DLinkedNode* next;

    DLinkedNode(int k, int v) :key(k), value(v), pre(nullptr), next(nullptr) {};//有键值初始化
    DLinkedNode() :key(0), value(0), pre(nullptr), next(nullptr) {};//无参数初始化

};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*>cache;//hash表
    DLinkedNode* head;//伪头
    DLinkedNode* tail;//伪尾
    int size;
    int capacity;


public:

    LRUCache(int _capacity) :capacity(_capacity), size(0) {
        head = new DLinkedNode();
        tail = new DLinkedNode();
        //初始化头尾相连
        head->next = tail;
        tail->pre = head;


    }


    int get(int key) {
        if(!cache.count(key)){//链表中没有该元素
            return -1;
        }


        DLinkedNode* node = cache[key];

        moveToHead(node);

        return node->value;


    }



    void put(int key, int value) {
        if (!cache.count(key)) {//不存在   创建节点 
            DLinkedNode* node = new DLinkedNode(key, value);

            cache[key] = node;
            
            addToHead(node);//添加到链表头部分

            size++;

            if (size > capacity) {//超出容量
                DLinkedNode* removed = removeTail();
                cache.erase(removed->key);
                delete removed;
                size--;
            }


        }

        else {

            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);

        }


    }
    void addToHead(DLinkedNode* node) {//新建节点
        //节点赋值
        node->pre = head;
        node->next = head->next;
        //双向链表修改
        head->next->pre = node;
        head->next = node;
    }
    void removeNode(DLinkedNode* node) {//删除节点
        node->pre->next = node->next;
        node->next->pre = node->pre;

    }
    void moveToHead(DLinkedNode* node) {//在链表中删除该节点，并将该节点移动到开头

        removeNode(node);
        addToHead(node);


    }
    DLinkedNode* removeTail() {//删除尾节点，返回地址
        DLinkedNode* node = tail->pre;
        removeNode(node);
        return node;
    }

    
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */