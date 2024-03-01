#include<iostream>
#include<vector>

using namespace std;


 // Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {//链表中元素删除
        auto p = head;
        auto q = p;
        while(p!=nullptr && p->val==val){//链表头元素检测
            p = p->next;
            head = p;//更新链表头
            
        }

        while (p != nullptr && p->next != nullptr) {///

            if (p->next->val == val) {
                q = p->next;
                p->next = p->next->next;
                delete q;
                continue;
            }
            p = p->next;
        }
        return head;

    }
};
int main() {
    vector <int> a = { 1, 2, 2, 1 };//问题
	cout << "kk123" << endl;
}

