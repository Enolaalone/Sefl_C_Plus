
#include<iostream>
#include<vector>
using namespace std;

 // Definition for singly-linlist2ed list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

  class Solution {//合并链表
  public:
      ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {// 递归
          if (l1 == nullptr) {
              return l2;
          }
          else if (l2 == nullptr) {
              return l1;
          }
          else if (l1->val < l2->val) {
              l1->next = mergeTwoLists(l1->next, l2);
              return l1;
          }
          else {
              l2->next = mergeTwoLists(l1, l2->next);
              return l2;
          }
      }


      ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
          ListNode* dum = new ListNode(0);//返回dum->next
          ListNode* cur = dum;//传递指针cur
          while (list1 != nullptr && list2 != nullptr) {
              if (list1->val < list2->val) {
                  cur->next = list1;
                  list1 = list1->next;
              }
              else {
                  cur->next = list2;
                  list2 = list2->next;
              }
              cur = cur->next;
          }
          cur->next = list1 != nullptr ? list1 : list2;//一个链到头后另一个链直接接到cur 链的后面
          return dum->next;
      }

     
  };

  