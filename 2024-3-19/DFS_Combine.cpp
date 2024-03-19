#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include <map>
using namespace std;

vector<int> a;
map<int,int>book;
void DFS(int cur ,int n,vector<int> &nums){

    if(cur==n){
        for (auto num:a)
        {
           cout<<num;
        }
        cout<<endl;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        if(!book[nums[i]]){
            a.push_back(nums[i]);
            book[nums[i]]=1;

            DFS(cur+1,nums.size(),nums);
            
            book[nums[i]]=0;
            a.pop_back();
        }
    }
    

}

int main() {
	vector<int>nums{ 1, 2, 3, 4 };
	DFS(0, 4, nums);

}
