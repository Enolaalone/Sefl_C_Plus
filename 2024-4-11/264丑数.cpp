#include<iostream>
#include<string>
#include<stdbool.h>
#include<stack>
#include<vector>
#include<map>
#include < algorithm >
#include <queue>
using namespace std;


class Solution {


public:

    int nthUglyNumber(int n) {
        priority_queue<double, vector<double>, greater<double> > que;
        double answer = 1;
        for (; n>1; n--)
        {
            que.push(2 * answer);
            que.push(3 * answer);
            que.push(5 * answer);
            answer = que.top();
            que.pop();

            while (!que.empty() && que.top() == answer) {
                que.pop();
            }

        }
        return answer;
    }
};






























