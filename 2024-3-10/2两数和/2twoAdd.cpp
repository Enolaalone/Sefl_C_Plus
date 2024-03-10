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
    // 读取对应位上的val 如果指针式null ，val就取0，
    //建立当前的节点sum%10,
    //进位carry=sum/10
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto dummy=new ListNode(0);
        auto pre=dummy;//辅助指针
        int carry=0;//进位

        while (l1!=nullptr||l2!=nullptr)
        {
            int n1=(l1!=nullptr)?l1->val:0;//l1链数字
            int n2=(l2!=nullptr)?l2->val:0;//l2链数字

            int sum=n1+n2+carry;//求和
            pre->next=new ListNode(sum%10);//下一位
            pre=pre->next;
            carry=sum/10;//求进位

            l1=(l1!=nullptr)?l1->next:nullptr;
            l2=(l2!=nullptr)?l2->next:nullptr;
        }

        if(carry)pre->next=new ListNode(carry,nullptr);
        return dummy->next;
    }
};

int main() {
    ListNode* dum1 = new ListNode(0);
    ListNode* dum2 = new ListNode(0);

    auto l1 = dum1, l2 = dum2;
    l2->val = 2;
    l2->next = nullptr;

    for (int i = 0; i < 2; i++)
    {
        l1->val = i;
        l1->next = new ListNode(0);
        l1 = l1->next;
    }
    l1->next = nullptr;
    l1->val = 2;

    Solution solution;
    ListNode* head = solution.addTwoNumbers(dum1, dum2);

    for (ListNode* i = head; i != nullptr; i=i->next)
    {
        printf("%d\n",i->val);
    }
    
}

