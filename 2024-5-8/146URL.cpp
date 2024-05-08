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
    int key, value;//��ֵ��

    DLinkedNode* pre;
    DLinkedNode* next;

    DLinkedNode(int k, int v) :key(k), value(v), pre(nullptr), next(nullptr) {};//�м�ֵ��ʼ��
    DLinkedNode() :key(0), value(0), pre(nullptr), next(nullptr) {};//�޲�����ʼ��

};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*>cache;//hash��
    DLinkedNode* head;//αͷ
    DLinkedNode* tail;//αβ
    int size;
    int capacity;


public:

    LRUCache(int _capacity) :capacity(_capacity), size(0) {
        head = new DLinkedNode();
        tail = new DLinkedNode();
        //��ʼ��ͷβ����
        head->next = tail;
        tail->pre = head;


    }


    int get(int key) {
        if(!cache.count(key)){//������û�и�Ԫ��
            return -1;
        }


        DLinkedNode* node = cache[key];

        moveToHead(node);

        return node->value;


    }



    void put(int key, int value) {
        if (!cache.count(key)) {//������   �����ڵ� 
            DLinkedNode* node = new DLinkedNode(key, value);

            cache[key] = node;
            
            addToHead(node);//��ӵ�����ͷ����

            size++;

            if (size > capacity) {//��������
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
    void addToHead(DLinkedNode* node) {//�½��ڵ�
        //�ڵ㸳ֵ
        node->pre = head;
        node->next = head->next;
        //˫�������޸�
        head->next->pre = node;
        head->next = node;
    }
    void removeNode(DLinkedNode* node) {//ɾ���ڵ�
        node->pre->next = node->next;
        node->next->pre = node->pre;

    }
    void moveToHead(DLinkedNode* node) {//��������ɾ���ýڵ㣬�����ýڵ��ƶ�����ͷ

        removeNode(node);
        addToHead(node);


    }
    DLinkedNode* removeTail() {//ɾ��β�ڵ㣬���ص�ַ
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