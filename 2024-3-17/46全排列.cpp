#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>

using namespace std;

class Solution {
public:
    vector<vector<int>>a;//初始二维数组
    map<int,int> book;
    vector<int> b;

    void DFS(int cur, int n, vector<int>& nums){//遍历次数 去除数个数 数组
        if (cur==n)
        {
            a.push_back(b);
            return;
  
        }

        for (int i = 0; i < n; i++)
        {
            if (!book[nums[i]])
            {
                b.push_back(nums[i]);
                book[nums[i]] = 1;
                DFS(cur + 1, nums.size(), nums);
                book[nums[i]] = 0;
                b.pop_back();

            }


        }


    }

    vector<vector<int>> permute(vector<int>& nums) {//返回值是二维数组
        DFS(0, nums.size(), nums);
        return a;

    }
};



int main() {
    vector<int> nums{ 1,2,3 };
    Solution solution;
    vector<vector <int>> k = solution.permute(nums);
    for (int i = 0; i < k.size(); i++)
    {
        for (int j = 0; j < 3; j++) {
            cout << k[i][j];
        }
        cout << endl;
    }

}