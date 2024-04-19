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
    int sumOddLengthSubarrays(vector<int>& arr) {
		if (arr.size() == 0)return 0;
		int num=0,k=1,j;
		vector<int>n(1,0);

		
		while (k < arr.size()) {
			for (size_t i = 0; i < arr.size()-n.size()+1; i++)
			{
				n = vector<int>(arr.begin()+ i, arr.begin() + i + k);
				for (size_t l = 0; l < n.size(); l++)
				{
					num += n[l];
				}
			}
			


		
			k += 2;
		}
		return num;


    }
};


class Solution {//前缀和
public:
	int sumOddLengthSubarrays(vector<int>& arr) {
		int num=0;
		vector<int>nums(arr.size()+1,0);//前缀和数组特点比原数组大一

		for (size_t i = 0; i < arr.size(); i++)//前缀和
		{
			nums[i + 1] = nums[i] + arr[i];

		}


		for (size_t i = 1; i <= arr.size(); i+=2)//当前子串长度小于父串长度；
		{
			for (size_t j = 0; j <arr.size()-i+1; j++)
			{
				num += nums[j+i] - nums[j];

			}

		}

		return num;


	}
};