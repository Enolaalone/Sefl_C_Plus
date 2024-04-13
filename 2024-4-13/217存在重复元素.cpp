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


//class Solution {
//private:
//    map<int, int>b;
//public:
//    bool containsDuplicate(vector<int>& nums) {
//        for (size_t i = 0; i < nums.size(); i++)
//        {
//            if (b[nums[i]] == 1)return true;
//            b[nums[i]] = 1;
//        }
//        return false;
//    }
//};

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> s;//��ϣ��
        for (int x : nums) {
            if (s.find(x) != s.end()) {//�ж�Ӧ��ֵ�ԣ���ָ���Ӧλ�ã�û�е�������ָ��end()
                return true;
            }
            s.insert(x);
        }
        return false;
    }
};

