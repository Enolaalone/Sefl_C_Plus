#include<iostream>
#include<string>
#include<stdbool.h>
#include<stack>
#include<vector>
#include<map>
#include < algorithm >
#include <queue>
#include<unordered_set>
#include<unordered_map>
using namespace std;



class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char,char>str_s,str_t;
    
        size_t i=0;
        vector<int> nums(256,0);
        while (s[i] != '\0' || t[i] != '\0') {
            char s1 = (s[i] != '\0') ? s[i] : '\0';
            char t1 = (t[i] != '\0') ? t[i] : '\0';

            if (str_s.find(s1) != str_s.end()&&str_s[s1]!=t1 ||
                str_t.find(t1) != str_t.end()&&str_s[t1]!=s1)//如果有映射，而且映射不等于当前另一个数组的值
                return false;

            str_s[s1] = t1;
            str_s[t1] = s1;


            i++;
            
        }

        
        return true;

    }
};


int main() {
    Solution solution;

    string s = "foo";
    string t = "bar";

    cout << solution.isIsomorphic(s, t);

    return 0;
}
