
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


//class Solution {
//public:
//    int firstUniqChar(string s) {
//		vector<int>num(256,0);
//		for (auto ch:s)
//		{
//			num[ch]++;
//		}
//
//		for (size_t i = 0; i < s.size(); i++)
//		{
//			if (num[s[i]] != 1)continue;
//			num[s[i]]--;
//			if (!num[s[i]])return i;
//		}
//		return -1;
//
//
//    }
//};


class Solution {
public:
	int firstUniqChar(string s) {
		unordered_map<char,bool>num;
		for (auto ch : s)
		{
			if (num.find(ch) == num.end())num[ch] = 1;
			else num[ch] = 0;
		}

		for (size_t i = 0; i < s.size(); i++)
		{
			if (num[s[i]] == 1)return i;

		}
		return -1;


	}
};