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
    bool isAnagram(string s, string t) {
        vector<int>s_num(256, 0), t_num(256, 0);
        //unordered_map<char, char>str_s, str_t;
        for (size_t i = 0; i < s.size(); i++)
        {
            s_num[s[i]]++;
            t_num[t[i]]++;


            if (s[i] == t[i])return 0;
        }
        for (size_t i = 0; i < s.size(); i++)
        {

            if (s_num[s[i]] != t_num[s[i]])return 0;

        }
        return 1;

    }
};

int main() {

    string s = "anagram", t = "nagaram";
    Solution solution;

    return solution.isAnagram(s, t);
}