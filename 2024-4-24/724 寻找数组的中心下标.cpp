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
    int pivotIndex(vector<int>& nums) {
        vector<int>sum(nums.size() + 1,0);//大一数组

        for (int i = 1; i < sum.size();i++) {//遍历1--前缀和数组大小==原来数组大小
            sum[i] = sum[i - 1] + nums[i-1];
        
        }

        for (size_t i = 1; i <= nums.size(); i++)
        {

            if( sum[i-1] == sum[sum.size() - 1] - sum[i])return i - 1;//返回在原始数组中的位置
        }
        return -1;

    }
};

int main() {


    Solution solution;
    vector<int>nums = { -1,-1,0,1,1,0 };

    return solution.pivotIndex(nums);
}