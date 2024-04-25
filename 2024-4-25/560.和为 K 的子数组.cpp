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
	int subarraySum(vector<int>& nums, int k) {
		vector<int>sum(nums.size() + 1, 0);//前缀和数组
		unordered_map<int, int>map;
		int n = 0;
		map[0] = 1;//表示当前前缀和为k的情况
		for (size_t i = 1; i <= nums.size(); i++)//从1开始构建前缀和数组
		{
			sum[i] = sum[i - 1] + nums[i - 1];//当前前缀和
			if (map[sum[i] - k])n += map[sum[i] - k];//有两前缀和之差=k的情况出现;
			//+map[sum[i]=k]是因为可能有负数，例如n为一个前缀和,因为负数之后又出现一个前缀和为n,此时考虑当前前缀和和之前这两个n之差都为k的情况
			map[sum[i]]++;
		}

		return n;

	}
};

int main() {
	Solution soluton;
	vector<int>nums = { 3,4,7,2,-3,1,4,2 };
	soluton.subarraySum(nums, 2);


}
//给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。

//子数组是数组中元素的连续非空序列。

