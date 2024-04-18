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

class NumArray {
    vector<int>nb;
public:
    NumArray(vector<int>& nums) {
       nb=  vector<int>(nums.size()+1,0);// 加1数组方便访问前缀和
       for (size_t i = 1; i <= nums.size(); i++)
       {
           nb[i] = nb[i - 1] + nums[i-1];//前一个加上nums当前值

       }
    }

    int sumRange(int left, int right) {

        return  nb[right + 1] - nb[left];//直接返回距离差值
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */