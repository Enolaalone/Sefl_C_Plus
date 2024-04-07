#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>
using namespace std;


class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int>nums(temperatures.size());//���ص�����
        stack<int> tem;//����ջ���������ϵݼ����洢���
        for (size_t i =0; i < temperatures.size(); i++)
        {

            while (!tem.empty()&&temperatures[tem.top()] < temperatures[i]) {//��ջ������ջ��Ԫ��С�ڵ�ǰԪ��
                nums[tem.top()]=i-tem.top();//ջ��Ԫ�أ���ǰԪ�����-վ��Ԫ�����
                tem.pop();//ɾ��վ��Ԫ��
            }
            tem.push(i);//��ǰԪ����ջ
     
        }
        return nums;


    }
};


int main() {
    vector<int> num{ 89,62,70,58,47,47,46,76,100,70 };
    Solution sulotion;
    vector<int>k(sulotion.dailyTemperatures(num));
    for (size_t i = 0; i < k.size(); i++)
    {
        cout << k[i] << endl;
    }

}