#include <vector>//动态区域
#include <iostream>
using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int num=0,max=0;
        for (int* i = &nums[0]; i < &nums[0]+nums.size(); i++)
        {
            if (*i==1)num++;
            else {
                if(num>max)
                max=num;
                num=0;
            }
            
        }
        if(num>max)max=num;
        return max;
    }
};



int main(){
    Solution solution;
    
    vector<int> a={1,1,1,9,1,1,1,8,1};
    int n=solution.findMaxConsecutiveOnes(a);
    cout<<n<<endl;
    return 0;
}
