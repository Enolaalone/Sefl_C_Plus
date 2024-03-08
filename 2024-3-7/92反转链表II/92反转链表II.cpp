
#include<iostream>
#include<stdlib.h>
//Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };



class Solution {
public:
    ListNode* end;//装n+1节点位置
    ListNode* reserve(ListNode* head,int n) {//将链表前n节点反转
        if (n == 1) {
            end = head->next;//记录n+1节点
            return head;
        }

        ListNode* last = reserve(head->next,n-1);//将head后的链表反转
        head->next->next = head;//将原来head->next的下一地址指向head
        head->next = end;//将head->next指向n+1号节点
        return last;//返回反转后的头节点
    }
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == 1) {
            return reserve(head, right);//反转 

        }

        head->next = reverseBetween(head->next, left - 1, right - 1);//递归到left节点处
        return head;
    }
};