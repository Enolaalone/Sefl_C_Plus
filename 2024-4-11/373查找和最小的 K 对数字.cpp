#include<iostream>
#include<string>
#include<stdbool.h>
#include<stack>
#include<vector>
#include<map>
#include < algorithm >
#include <queue>
using namespace std;


//class Solution {//��ʱ
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
        auto cmp = [&nums1, &nums2](const pair<int, int> &a, const pair<int, int> &b)->bool {//Lambda����
            
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];//�ȽϹ���a,b����µ����������
        
            };
        priority_queue<pair<int,int>, vector<pair<int, int>>, decltype(cmp) > r(cmp);//��ά������У�decltype(cmp)����ȽϹ���ͷ���ֵ
        vector<vector<int> > kb;

        for (size_t j = 0; j < min<size_t>(nums2.size(), k); j++)//�Ƚϵó���Ӷ���Ŀ��
        {

            r.emplace(0,j);//��1�����1��Ԫ����ź�2�������ż�����У����Ƚϣ�

        }

        for (; k-->0&&!r.empty();)
        {
            pair<int,int>num = r.top();//������С�Ķ�ֵ
            r.pop();
            kb.emplace_back(vector<int>{nums1[num.first], nums2[num.second]});//����ֵ�����ά����
            if (num.first+1<nums1.size()) {//��ȫ1�������2��Ԫ����ź�2��������

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