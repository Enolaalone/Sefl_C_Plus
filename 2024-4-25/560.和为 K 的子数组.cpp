#include<iostream>
#include<string>
#include<cstdbool>
#include<stack>
#include<vector>
#include<map>
#include <algorithm>
#include <queue>
#include<unordered_set>
#include<unordered_map>
using namespace std;

class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		vector<int>sum(nums.size() + 1, 0);//ǰ׺������
		unordered_map<int, int>map;
		int n = 0;
		map[0] = 1;//��ʾ��ǰǰ׺��Ϊk�����
		for (size_t i = 1; i <= nums.size(); i++)//��1��ʼ����ǰ׺������
		{
			sum[i] = sum[i - 1] + nums[i - 1];//��ǰǰ׺��
			if (map[sum[i] - k])n += map[sum[i] - k];//����ǰ׺��֮��=k���������;
			//+map[sum[i]=k]����Ϊ�����и���������nΪһ��ǰ׺��,��Ϊ����֮���ֳ���һ��ǰ׺��Ϊn,��ʱ���ǵ�ǰǰ׺�ͺ�֮ǰ������n֮�Ϊk�����
			map[sum[i]]++;
		}

		return n;

	}
};

int main() {
	Solution soluton;
	vector<int>nums = { 3,4,7,2,-3,1,4,2 };
	soluton.subarraySum(nums, 2);


}
//����һ���������� nums ��һ������ k ������ͳ�Ʋ����� �������к�Ϊ k ��������ĸ��� ��

//��������������Ԫ�ص������ǿ����С�

