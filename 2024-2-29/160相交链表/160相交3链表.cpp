#include <vector>//动态区域
#include <iostream>
using namespace std;

//  Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        auto pA=headA,pB=headB;
        while (pA!=pB)
        {
            pA= pA!=nullptr ? pA->next: pA=headB;//条件语句： 如果pA!=null pA=pA->next 否则pA=headB
            pB= pB!=nullptr ? pB->next: pB=headA;

        }
        return pA;
        
        
    }
};

int main(){
    vector<int> a={0,1,0,2,3};
    Solution solution;


    
    return 0;
}
