#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

struct ListNode
{
    int val;
    ListNode*next;
    ListNode(int x):val(x),next(nullptr){}

};

//反转链表函数
ListNode* reverseList(ListNode* head)
{
    ListNode* prev = nullptr;
    ListNode* curr = head;
    ListNode* prev1 = nullptr;
    int n = 1;
    if(curr->next == nullptr)
    {
        return nullptr;
    }
    else if(curr->next->next == nullptr)
    {
        return curr->next;
    }
    else
    {
    while(curr)
    {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        //curr->next = prev; //反转指针

        //curr = next;
    }
    //int n = 1;
    for(int i = 1;i<n-1;i++)
    {
        if(!prev->next)return head; //n超过链表长度，直接返回
        prev = prev->next;

    }

    //删除节点
    ListNode* nodeToDelete = prev->next;
    if(nodeToDelete)
    {
        prev->next = nodeToDelete->next;
        delete nodeToDelete;
    }

    while(prev)
    {
       // ListNode* prev1 = nullptr;
        ListNode* next = prev->next;

        prev->next = prev1;
        prev1 = prev;
        prev = next;
    }
}
    return prev1;
    
    //return prev;


    //return prev;

}



//删除倒数第N个节点
ListNode* removeNthFromEnd(ListNode* head,int n)
{
    ListNode* dummy = new ListNode(0); //虚拟头节点
    dummy->next = head;
    ListNode* fast = dummy;
    ListNode* slow = dummy;

    //快指针先走n+1步，使得快慢指针相距n
    for(int i = 0;i<=n;i++)
    {
        fast = fast->next;
    }

    //快慢指针同时移动，直到快指针到达链表末尾
    while(fast)
    {
        fast = fast->next;
        slow = slow->next;
    }

    //删除倒数第n个节点
    ListNode* nodeToDelete = slow->next;
    slow->next = slow->next->next;
    delete nodeToDelete;

    ListNode* newHead = dummy->next;
    delete dummy;
    return newHead;
}
//打印
void printList(ListNode* head)
{
    while(head)
    {
        cout<<head->val<<" ";
        head = head->next;
    }
    cout<<endl;
    
}



// 主函数，测试链表反转
int main() {
    // 创建链表：1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    // head->next->next = new ListNode(3);
    // head->next->next->next = new ListNode(4);
    // head->next->next->next->next = new ListNode(5);

    cout << "原链表: ";
    printList(head);

    // 反转链表
    //head = reverseList(head);
    int n  = 2;
    head = removeNthFromEnd(head,n);

    cout << "反转后: ";
    printList(head);

    return 0;
}