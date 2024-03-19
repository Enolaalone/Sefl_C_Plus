#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<int> nums;
        stack<string> str;
        int num=0;
        string res="";

        for (auto ch:s)
        {
            if (ch >= '0' && ch <= '9') {//Êý×Ö

                num = 10 * num + (int)(ch - '0');
            }
            else if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') {
                res += ch;
            }
            else if (ch=='[')
            {
                str.push(res);
                res = "";
                nums.push(num);
                num = 0;
            }
            else if(ch==']')
            {
                int times = nums.top();
                nums.pop();

                for (int i = 0; i < times; i++)
                {
                    str.top() += res;

                }
                res = str.top();
                str.pop();

            }
            

        }
        return res;

    }
};



int main() {
    Solution solution;
    string k = "3[a2[c]b]";
    k = solution.decodeString(k);



}