#include<iostream>
#include<string>
#include<stdbool.h>
#include<stack>
#include<vector>
#include<map>
#include < algorithm >
#include <queue>
#include<unordered_set>
using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int>s;
        unordered_set<int>k1;
        vector<int>k;
        for (int x:nums1)
        {
            s.insert(x);
        }
        for (int x : nums2)
        {
            if (s.find(x) != s.end())k1.insert(x);
        }
        for (auto its = k1.begin();  its!=k1.end(); its++)
        {
      
            k.push_back(*its);
        }
        return k;


    }
};