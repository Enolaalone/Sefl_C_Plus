#include<iostream>
#include<string>
#include<cstdbool>
#include<stack>
#include<vector>
#include<map>
#include <algorithm>
#include <queue>
#include<unordered_set>
#include<unordered_map>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>>str;//邻接表式的数据结构很重要！！！


        for (auto ch:strs)//遍历字符串数组
        {
            string s=ch;
            sort(s.begin(), s.end());//左闭右开  排序

            str[s].push_back(ch);//排序一致的字符串就加入同一vector

        }


        vector<vector<string>> ans;
        for (unordered_map<string, vector<string>>::iterator iter = str.begin();iter!=str.end();iter++)//注意迭代器需要指定类型
        {
            ans.push_back((*iter).second);
        }
        return ans;


    }
};