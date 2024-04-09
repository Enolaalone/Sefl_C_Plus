#include<iostream>
#include<string>
#include<stdbool.h>
#include<stack>
#include<vector>
#include<map>
#include < algorithm >
using namespace std;

class MyQueue {
public:
    stack<int> n1;
    stack<int> n2;
    MyQueue() {

    }

    void push(int x) {
        n1.push(x);
    }

    int pop() {
        int n,num;
        if (n1.empty()) return 0;
        num=n1.size();
        for (size_t i = 0; i < num; i++)
        {
            n2.push(n1.top());
            n1.pop();
        }
        n = n2.top();
        n2.pop();
        num = n2.size();
        for (size_t i = 0; i < num; i++)
        {
            n1.push(n2.top());
            n2.pop();
        }
        return n;

    }

    int peek() {
        int n,num;
        num = n1.size();
        for (size_t i = 0; i < num; i++)
        {
            n2.push(n1.top());
            n1.pop();
        }
        n = n2.top();
        num = n2.size();
        for (size_t i = 0; i < num; i++)
        {
            n1.push(n2.top());
            n2.pop();
        }
        return n;
    }

    bool empty() {
        return n1.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */


int main(){

    MyQueue my;

    my.push(1);


    cout << my.pop() << endl;
    cout << my.empty() << endl;

    return 0;
}