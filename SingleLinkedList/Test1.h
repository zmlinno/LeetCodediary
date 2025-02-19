#include<iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode*next;
    ListNode(int x):val(x),next(nullptr){}

};

//在链表中反转k值
ListNode* reverKNodes(ListNode* head,int k)
{
        if(!head||k<=1)return head;

        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next = nullptr;

        ListNode* tail = head;
        for(int i = 0;i<k&&head;i++)
        {
                tail = tail->next;
        }

        for(int i = 0;i<k&&curr;i++)
        {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
        }

        head->next = tail;

        return prev;
}


void printList(ListNode* head)
{
        while(head)
        {
                cout<<head->val<<" -> ";
                head = head->next;
        }
        cout<<"nullptr"<<endl;
}


//创建链表
ListNode* createList(initializer_list<int>vals)
{
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        for(int v: vals)
        {
                tail->next = new ListNode(v);
                tail = tail->next;
        }
        return dummy->next;
}