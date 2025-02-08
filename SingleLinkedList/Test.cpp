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

    while(curr)
    {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        //curr->next = prev; //反转指针

        //curr = next;
    }
    return prev;

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
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    cout << "原链表: ";
    printList(head);

    // 反转链表
    head = reverseList(head);

    cout << "反转后: ";
    printList(head);

    return 0;
}