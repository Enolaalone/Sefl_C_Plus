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
    ListNode* removeElements(ListNode* head, int val) {//������Ԫ��ɾ��
        auto p = head;
        auto q = p;
        while(p!=nullptr && p->val==val){//����ͷԪ�ؼ��
            p = p->next;
            head = p;//��������ͷ
            
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
    vector <int> a = { 1, 2, 2, 1 };//����
	cout << "kk123" << endl;
}

