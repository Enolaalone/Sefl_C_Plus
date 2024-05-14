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

/// <summary>
/// ����һ���������� nums������ ���� answer ������ answer[i] ���� nums �г� nums[i] ֮�������Ԫ�صĳ˻� ��
//��Ŀ���� ��֤ ���� nums֮������Ԫ�ص�ȫ��ǰ׺Ԫ�غͺ�׺�ĳ˻�����  32 λ ������Χ�ڡ�
//
//�� ��Ҫʹ�ó��������� O(n) ʱ�临�Ӷ�����ɴ��⡣
//
//
//
//ʾ�� 1:
//
//����: nums = [1, 2, 3, 4]
//��� : [24, 12, 8, 6]
//ʾ�� 2 :
//
//	���� : nums = [-1, 1, 0, -3, 3]
//	��� : [0, 0, 9, 0, 0]
/// </summary>


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
		vector<int> K(nums.size());
		vector<int> L(nums.size()); L[0] = 1;
		vector<int> R(nums.size()); R[nums.size() - 1] = 1;

		for (int i = 1; i < nums.size(); i++)
		{
			L[i] = L[i - 1] * nums[i - 1];

		}

		for (int i = nums.size() -1; i>0 ; i--)
		{
			R[i-1] = R[i] * nums[i];

		}


		for (size_t i = 0; i < nums.size(); i++)
		{
			K[i] = L[i] * R[i];
		}

		return K;

    }
};