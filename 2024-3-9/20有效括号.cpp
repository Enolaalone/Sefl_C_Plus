#include<iostream>
#include<string>
#include<stack>
using namespace std;
class Solution {
public:
    bool isValid(string s) {
        int i=0;
        char ch;
        stack<char> ps;
        while (s[i] != '\0') {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
                ps.push(s[i]);
            else if (s[i] == ')' && ps.size())
            {
                ch = ps.top();
                ps.pop();
                if (ch != '(')return false;
            }
            else if (s[i] == ']' && ps.size())
            {
                ch = ps.top();
                ps.pop();
                if (ch != '[')return false;
            }
            else if (s[i] == '}' && ps.size())
            {
                ch = ps.top();
                ps.pop();
                if (ch != '{')return false;
            }
            else return false;
            i++;

        }
        if(ps.size())
        {
            return false;
        }else return true;

    }
};

int main() {
    Solution solution;
    string str("]");
    cout << solution.isValid(str) << endl;

}