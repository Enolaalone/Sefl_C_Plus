#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>
#include < algorithm >
using namespace std;


class Solution {
public:
    
    int largestRectangleArea(vector<int>& heights) {
        stack<int>nums;
        int Max=0,w,l;
        if (heights.size()==1)
        {
            return Max;
        }
        for (size_t i = 0; i < heights.size(); i++)
        {
            while (!nums.empty()&&heights[nums.top()]>heights[i])
            {
                l = heights[nums.top()];
                nums.pop();
                w = i;
                if (!nums.empty())
                {
                    w -= nums.top() + 1;
                }
                Max = max(Max, w * l);

            }
            nums.push(i);
        }
        while (!nums.empty())
        {
            l = heights[nums.top()];
            nums.pop();
            w =heights.size();
            if (!nums.empty())
            {
                w -= nums.top() + 1;
            }
            Max = max(Max, w * l);

        }



        return Max;

    }
};


int main() {
    vector<int> num{ 2,1,5,6,2,3 };
    Solution sulotion;
    int k = sulotion.largestRectangleArea(num);

    cout << k << endl;


}