#include<iostream>
#include<string>
#include<stack>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
class Solution {
public:
    ListNode* reverse(ListNode* head) {//反转链表
        if (head->next == nullptr) {
            return head;
        }
        ListNode* last = reverse(head->next);                   
        head->next->next = head;
        head->next = nullptr;
        return last;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //反转链表
        l1 = reverse(l1);
        l2 = reverse(l2);

        int num1 = 0, num2 = 0;
        while (l1!= nullptr) {
            num1 = 10 * num1 + l1->val;
            l1 = l1->next;
        }
        while (l2!= nullptr) {
            num2 = 10 * num2 + l2->val;
            l2 = l2->next;
        }

        int res = num1 + num2,k;

        auto dum = new ListNode(0);
        auto l = dum;

        //auto n = new ListNode(0);
        //l->next = n;
        //l = l->next;

        //k = res % 10; 
        //l->val = k;
        //l->next = nullptr;
        //res /= 10;
        while(1) {
            if (res != 0)
            {
                auto n = new ListNode(0);
                l->next = n;
                l = l->next;

                k = res % 10;
                l->val = k;
                l->next = nullptr;
                res /= 10;
            }
            else { 
                auto n = new ListNode(0);
                l->next = n;
                l = l->next;
                l->val = k;
                l->next = nullptr;
                break;
            }

        }
        return dum->next;



    }
};

int main() {
    ListNode* dum1 = new ListNode(0);
    ListNode* dum2 = new ListNode(0);
    auto l1 = dum1, l2 = dum2;
    l2->val = 9;
    l2->next = nullptr;

    for (int i = 0; i < 3; i++)
    {
        l1->val = i;
        l1->next = new ListNode(0);
        l1 = l1->next;
    }
    l1->next = nullptr;
    l1->val = 9;

    Solution solution;
    ListNode* head = solution.addTwoNumbers(dum1, dum2);
}

