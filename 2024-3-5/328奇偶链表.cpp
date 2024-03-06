#include<iostream>
#include<vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
		ListNode* dum1 = new ListNode(0);
		ListNode* dum2 = new ListNode(0);
		dum1->next = head;
		ListNode* cur = dum1->next;
		ListNode* cur2 = dum2;

		if(dum1->next==nullptr)return dum1->next;
		while (cur!=nullptr)
		{
			cur2->next = cur->next;
			if (cur->next == nullptr) break;
			if (cur->next->next == nullptr) break;
			cur->next = cur->next->next;

			cur2 = cur2->next;
			cur = cur->next;
		}

		cur->next = dum2->next;
		return dum1->next;

    }
};