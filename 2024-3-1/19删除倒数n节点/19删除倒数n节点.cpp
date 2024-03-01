#include<iostream>
#include<vector>
#include<stdlib.h>
using namespace std;


// Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {//Ë«Ö¸Õë
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto p = head,q=p;
  
        for (int i = 0; i < n && p->next!=nullptr; i++)
        {
            p = p->next;
        }
            

        while (p->next!=nullptr)
        {
            q = q->next;
            p = p->next;
        }
        if (q->next != nullptr) {
            p = q->next;
            q->next = q->next->next;
            delete p;
            return head;
        }
        else return nullptr;
        

    }
};

int main() {
    vector <int> a = { 1, 2, 2, 1 };//ÎÊÌâ
    Solution solution;
    ListNode* p;
    p = (ListNode*)malloc(sizeof(ListNode));
    p->next = nullptr;
    p->val = 0;
    solution.removeNthFromEnd(p,1);
    
}
