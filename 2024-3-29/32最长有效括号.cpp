#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include < map >
#include < algorithm >

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int length = s.size();
        int max_num = 0;
        vector<int> dp(length, 0);
        for (int i = 1; i < length; i++)
        {
            if (s[i] == ')')
            {
                if (s[i - 1] == '(')
                {
                    dp[i] = 2;
                    if (i - 2 >= 0) {
                        dp[i] = dp[i] + dp[i - 2];
                    }

                }
                else if (dp[i - 1] > 0) {
                    if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
                    {
                        dp[i] = dp[i - 1] + 2;
                        if (i - dp[i - 1] - 2 >= 0)
                        {
                            dp[i] += dp[i - dp[i - 1] - 2];
                        }
                    }




                }
            }


            max_num = max(max_num, dp[i]);
        }
        return max_num;

    }
};
















//class Solution {
//public:
//    int longestValidParentheses(string s) {
//        stack<char>str;
//        int num=0,i,max=0;
//        
//
//        for (i = 0; s[i] != '\0';i++) {
//            if(s[i]=='(')
//            {
//                str.push('(');
//            }
//            else if(s[i]==')'&&str.size())
//            {
//                if (str.top() == '(') {
//                    num += 2;
//                    str.pop();
//                }
//
//                if (str.empty())
//                {
//                    if (num > max)
//                        max = num;
//                    if (s[i + 1] != '(')
//                        num = 0;
//                }
//               
//            }
//
//    
//        }
//        if (num > max&&str.empty())max = num;
//        return max;
//    }
//};