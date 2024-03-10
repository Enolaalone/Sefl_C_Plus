#include<iostream>
#include<string>
#include<stack>
using namespace std;
class MinStack {
public:
    /** initialize your data structure here. */
    stack <int> ps,min;
    MinStack() {
       
    }

    void push(int x) {
        ps.push(x);
        if (min.empty() || min.top() >= x) min.push(x);//����minջ��Ԫ��Ϊ��С��
    }

    void pop() {
        if (ps.top() == min.top()) min.pop();//ps����С������min����Сͬ������
        ps.pop();
    }

    int top() {
        return ps.top();

    }

    int getMin() {
        return min.top();

    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */