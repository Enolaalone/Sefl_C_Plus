#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>

using namespace std;
class Solution{
public:
    string decodeString(string s) {
        stack<string> str;
        stack<int> nums;
        int num=0;
        string res="";
        for (auto ch:s)
        {
            if(ch>='0'&&ch<='9'){
                num=num*10+(int)(ch-'0');
            
            }
            else if(ch>='a' && ch<='z'||ch>='A'&& ch<='Z')
            {
                res+=ch;
            }
            else if(ch=='[')
            {
                nums.push(num);
                num=0;
                str.push(res);
                res="";

            }
            else if(ch==']')
            {
                int times=nums.top();
                nums.pop();
                for (int i = 0; i < times; i++)
                {
                    str.top()+=res;
                }
                res=str.top(); 
                str.pop() ;
            }
        }

        return res;
    }


};



int main() {
    Solution solution;
    string k = "3[a2[c]b]";
    k = solution.decodeString(k);
    for (auto i :k)
    {
        cout<<i;
    }
    

}