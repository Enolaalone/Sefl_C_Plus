 
#include <vector>//动态区域
#include <iostream>
using namespace std;
// Definition for singly-linked list.

struct ListNode {//链表
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {//交换两个节点的位置---迭代
        auto demmy=new ListNode(0,head);//建立一块区域作为中转结构体，将地址给demo0
        auto demo0=demmy;//哨兵节点demo0
        auto demo1=head;//首节点
        

        while(demo1&& demo1->next){//至少两个节点
            auto demo2=demo1->next;//节点2
            auto demo3=demo2->next;//节点3

            demo0->next=demo2;//中转节点->节点2
            demo2->next=demo1;//节点2->节点1
            demo1->next=demo3;//节点1->节点3

            demo0= demo1;//demo0指向head 和 demo1指向下一个交换的首
            demo1= demo3;

        }
        return demmy->next;
    }

    ListNode* swapPairs2(ListNode*head){//递归法
        if(head==nullptr || head->next==nullptr) return head;
    
        auto demo1=head;//首节点
        auto demo2=head->next;//次节点
        auto demo3=demo2->next;//下一个首节点

        demo2->next=demo1;//2->1
        demo1->next=swapPairs2(demo3);//1->3
        
        return demo2;
    }
    
};

int main(){
    Solution solution;

    
    return 0;
}
