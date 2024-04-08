#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>
#include < algorithm >
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int sum=0,Min;
        stack<int>pole;

        for (size_t i = 0; i < height.size(); i++)
        {
            while (!pole.empty()&&height[i]>height[pole.top()])//�����ݼ�ջ
            {
                int dp = height[pole.top()];//��ˮ������
                pole.pop();

                if (pole.empty())//���ջ�գ�˵����ǽû�У�ֱ�ӽ���
                     break;
                
                int distance = i - pole.top() - 1;//��ˮ����Ŀ�
                Min = min(height[pole.top()], height[i]);//dp�Ľ�ˮ���ޣ�ȡ������ǽ����ǽ
                sum += distance * (Min-dp);

            }


            pole.push(i);
        }
        return sum;



    }
};



int main() {
    vector<int> num{ 4,2,0,3,2,5 };
    Solution sulotion;
    int k=sulotion.trap(num);
    cout<< k << endl;
}