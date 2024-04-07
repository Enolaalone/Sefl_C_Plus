#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>
using namespace std;


class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int>nums(temperatures.size());//返回的数组
        stack<int> tem;//单调栈，由下向上递减，存储序号
        for (size_t i =0; i < temperatures.size(); i++)
        {

            while (!tem.empty()&&temperatures[tem.top()] < temperatures[i]) {//出栈条件：栈内元素小于当前元素
                nums[tem.top()]=i-tem.top();//栈中元素：当前元素序号-站内元素序号
                tem.pop();//删除站内元素
            }
            tem.push(i);//当前元素入栈
     
        }
        return nums;


    }
};


int main() {
    vector<int> num{ 89,62,70,58,47,47,46,76,100,70 };
    Solution sulotion;
    vector<int>k(sulotion.dailyTemperatures(num));
    for (size_t i = 0; i < k.size(); i++)
    {
        cout << k[i] << endl;
    }

}