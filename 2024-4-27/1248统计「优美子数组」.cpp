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
    int numberOfSubarrays(vector<int>& nums, int k) {//滑动窗口超时

        int ans = 0;
        int i = 1;//原来odd个数

        vector<int>odd(1, -1);

        for (size_t j = 0; j <=nums.size(); j++)
        {
            if (j == nums.size() || nums[j] & 1)//nums[j]&1判断为奇数
                odd.push_back(j);


            if (odd.size()-i>k) {
            
                int left = odd[i] - odd[i - 1];
                int right = j - odd[odd.size() - 2];
                ans += left * right;
                i++;
            
            }

        }


        return ans;

    }
};

//class Solution {
//public:
//    int numberOfSubarrays(vector<int>& nums, int k) {//滑动窗口超时
//
//        int number = 0;
//        for (size_t i = 0; i < nums.size() ; i++)//数组转化为0 1奇偶序列
//        {
//            if (nums[i] % 2 == 1)nums[i] = 1;
//            else nums[i] = 0;
//            
//        }
//
//        vector<int>num(nums.size() + 1);//前缀和数组
//        for (size_t i = 1; i <=nums.size(); i++)
//        {
//            num[i] = num[i - 1] + nums[i - 1];
//        }
//
//        for (size_t i = k; i <= nums.size(); i++)
//        {
//            for (size_t j = 0; j <= nums.size()-i; j++)
//            {
//                if (num[j+i]-num[j] == k)number++;
//            }
//        }
//
//
//        return number;
//    }
//};

//class Solution {
//public:
//    int numberOfSubarrays(vector<int>& nums, int k) {//滑动窗口超时
//
//        int number=0;
//        for (size_t i = 0; i < nums.size()-k+1; i++)
//        {
//
//            for (size_t j = 0; j < nums.size()-k-i+1; j++)
//            {
//                vector<int>num(nums.begin()+j, nums.begin() + k + i+j);
//                int n = 0;
//                for (size_t k = 0; k < num.size(); k++)
//                {
//                    if (num[k] % 2 != 0)n++;
//                }
//                if (n == k)number++;
//            }
//        }
//
//
//        return number;
//    }
//};