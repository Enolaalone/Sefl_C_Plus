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
        unordered_map<string,vector<string>>str;//�ڽӱ�ʽ�����ݽṹ����Ҫ������


        for (auto ch:strs)//�����ַ�������
        {
            string s=ch;
            sort(s.begin(), s.end());//����ҿ�  ����

            str[s].push_back(ch);//����һ�µ��ַ����ͼ���ͬһvector

        }


        vector<vector<string>> ans;
        for (unordered_map<string, vector<string>>::iterator iter = str.begin();iter!=str.end();iter++)//ע���������Ҫָ������
        {
            ans.push_back((*iter).second);
        }
        return ans;


    }
};