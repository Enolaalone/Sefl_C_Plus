#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>
#include < algorithm >
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int sum=0,Min;
        stack<int>pole;

        for (size_t i = 0; i < height.size(); i++)
        {
            while (!pole.empty()&&height[i]>height[pole.top()])//单调递减栈
            {
                int dp = height[pole.top()];//接水的下线
                pole.pop();

                if (pole.empty())//如果栈空，说明左墙没有，直接结束
                     break;
                
                int distance = i - pole.top() - 1;//接水区域的宽
                Min = min(height[pole.top()], height[i]);//dp的接水上限，取决于左墙和右墙
                sum += distance * (Min-dp);

            }


            pole.push(i);
        }
        return sum;



    }
};



int main() {
    vector<int> num{ 4,2,0,3,2,5 };
    Solution sulotion;
    int k=sulotion.trap(num);
    cout<< k << endl;
}