#include <vector>//动态区域
#include <iostream>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int p=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]!=val){
                nums[p]=nums[i];
                p++;
}
}
        return p;

    }
};

int main(){
    vector<int> a={0,1,0,2,3};
    Solution solution;

    
    
    return 0;
}
