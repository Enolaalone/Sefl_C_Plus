#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

class Solution {
public:
    stack <int> s;
    int evalRPN(vector<string>& tokens) {
        for (auto ch: tokens)
        {
            if (ch == "+" || ch == "-" || ch == "*" || ch == "/") {
                int R = s.top(); s.pop();//ÓÒ²Ù×÷ÊýR Õ»¶¥
                int L = s.top(); s.pop();
                if (ch == "+") s.push(L + R);
                if (ch == "-") s.push(L - R);
                if (ch == "*") s.push(L * R);
                if (ch == "/") s.push(L / R);
            }
            else
            {
                s.push(stoi(ch));
            }

        }

        int result = s.top(); s.pop();
        return result;

    }
};