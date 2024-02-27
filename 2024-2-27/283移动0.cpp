#include <vector>//动态区域
#include <iostream>
using namespace std;


class Solution {
public:
    void moveZeroes(vector<int>& nums) {//l,r为双指针
        int l=0;
        for (int r = 0; r < nums.size(); r++)
        {
            if(nums[r]){//如果右边数大于零
                swap(nums[l],nums[r]);
                l++;
            }
        }
        
    }
};

int main(){
    vector<int> a={0,1,0,2,3};
    Solution solution;
    solution.moveZeroes(a);
    for (int i = 0; i < a.size(); i++)
    {
        cout<<a[i]<<",";
    }
    
    return 0;
}
