#include<iostream>
#include<string>
#include<stdbool.h>
#include<stack>
#include<vector>
#include<map>
#include < algorithm >
#include <queue>
using namespace std;


//class Solution {//超时
//public:
//
//    struct Compare
//    {
//        bool operator() (const vector<int>& a, const vector<int>& b) {
//            return ((a[0] + a[1]) > (b[0] + b[1]));
//        }
//    };
//    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
//
//        priority_queue<vector<int>, vector<vector<int>>, Compare > r;
//        vector<vector<int> > kb;
//
//        for (size_t j = 0; j < nums1.size(); j++)
//        {
//            for (size_t i = 0; i < nums2.size(); i++)
//            {
//                vector<int> n;
//                n.push_back(nums1[j]);
//                n.push_back(nums2[i]);
//                r.push(n);
//
//            }
//        }
//        for (size_t i = 0; i < k; i++)
//        {
//            kb.push_back(r.top());
//            r.pop();
//        }
//        return kb;
//
//
//    }
//};

class Solution {
public:

    //struct Compare
    //{
    //    bool operator() (const vector<int>& a, const vector<int>& b) {
    //        return ((a[0] + a[1]) > (b[0] + b[1]));
    //    }
    //};
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto cmp = [&nums1, &nums2](const pair<int, int> &a, const pair<int, int> &b)->bool {//Lambda函数
            
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];//比较规则，a,b序号下的两个数组和
        
            };
        priority_queue<pair<int,int>, vector<pair<int, int>>, decltype(cmp) > r(cmp);//二维数组队列，decltype(cmp)传入比较规则和返回值
        vector<vector<int> > kb;

        for (size_t j = 0; j < min<size_t>(nums2.size(), k); j++)//比较得出添加对数目，
        {

            r.emplace(0,j);//将1数组的1号元素序号和2数组的序号加入队列，并比较；

        }

        for (; k-->0&&!r.empty();)
        {
            pair<int,int>num = r.top();//返回最小的对值
            r.pop();
            kb.emplace_back(vector<int>{nums1[num.first], nums2[num.second]});//将对值加入二维数组
            if (num.first+1<nums1.size()) {//补全1号数组的2号元素序号和2数组的序号

                r.emplace(num.first+1,num.second);

            }

        }

        return kb;


    }
};

int main() {
    Solution solution;
    vector<int>nums1 = { 1, 2, 4, 5, 6 };
    vector<int>nums2 = { 3,5,7,9 };

    solution.kSmallestPairs(nums1, nums2,20);

    return 0;
}