#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>
#include < algorithm >
using namespace std;


class MyCircularDeque {//ѭ������

private:
    vector<int> arr;//����
    int front;//ͷ
    int rear;//β
    int capacity;//��С

public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {//��ʼ��
        capacity = k + 1;
        arr.assign(capacity, 0);

        front = 0;
        rear = 0;
    }

    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if (isFull()) {
            return false;
        }
        front = (front - 1 + capacity) % capacity;//��ֹԽ����Ҫ+capacity��ȡ��
        arr[front] = value;
        return true;
    }

    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if (isFull()) {
            return false;
        }
        arr[rear] = value;
        rear = (rear + 1) % capacity;//rearʼ��ָ����ǿ�λ��
        return true;
    }

    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if (isEmpty()) {
            return false;
        }
        // front �����������Ŀ�ͷ�������� +1
        front = (front + 1) % capacity;
        return true;
    }

    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if (isEmpty()) {
            return false;
        }
        // rear ������������ĩβ�������� -1
        rear = (rear - 1 + capacity) % capacity;//��ֹԽ����Ҫ+capacity��ȡ��
        return true;
    }

    /** Get the front item from the deque. */
    int getFront() {
        if (isEmpty()) {
            return -1;
        }
        return arr[front];
    }

    /** Get the last item from the deque. */
    int getRear() {
        if (isEmpty()) {
            return -1;
        }
        // �� rear Ϊ 0 ʱ��ֹ����Խ��
        return arr[(rear - 1 + capacity) % capacity];
    }

    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return front == rear;//��ͷ�ͽ�βλ���Ƿ����
    }

    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        // ע�⣺�������Ƿǳ����������
        return (rear + 1) % capacity == front;//ѭ�����У�������+1ȡ��λ��Ϊ��ͷ
    }
};




/*
class MyCircularDeque {
private:
    vector<int> nums;
    int size;

public:

    MyCircularDeque(int k) {
        //nums = vector<int>(k);//��ֵ��ʽ
        size = k;
    }

    bool insertFront(int value) {
        if (nums.size()==size)return false;

        nums.insert(nums.begin(), value);
        return true;
    }

    bool insertLast(int value) {
        if (nums.size() == size)return false;

        nums.insert(nums.end(), value);
        return true;
    }

    bool deleteFront() {
        if (!nums.size())return false;
        nums.erase(nums.begin());
        return true;
    }

    bool deleteLast() {
        if (!nums.size())return false;
        nums.erase(nums.end()-1);
        return true;
    }

    int getFront() {
        if (!nums.size())return -1;
        return nums[0];
    }

    int getRear() {
        if (!nums.size())return -1;
        return nums[nums.size()-1];
    }

    bool isEmpty() {
        if (!nums.size())return true;
        else return false;
    }

    bool isFull() {
        if (nums.size() == size)return true;
        else return false;
    }
};
*/

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */




int main() {
    
    return 0;
}