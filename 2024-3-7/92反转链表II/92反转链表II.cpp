
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
    ListNode* end;//װn+1�ڵ�λ��
    ListNode* reserve(ListNode* head,int n) {//������ǰn�ڵ㷴ת
        if (n == 1) {
            end = head->next;//��¼n+1�ڵ�
            return head;
        }

        ListNode* last = reserve(head->next,n-1);//��head�������ת
        head->next->next = head;//��ԭ��head->next����һ��ַָ��head
        head->next = end;//��head->nextָ��n+1�Žڵ�
        return last;//���ط�ת���ͷ�ڵ�
    }
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == 1) {
            return reserve(head, right);//��ת 

        }

        head->next = reverseBetween(head->next, left - 1, right - 1);//�ݹ鵽left�ڵ㴦
        return head;
    }
};