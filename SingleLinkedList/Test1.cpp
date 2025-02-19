#include<iostream>
#include"Test1.h"


int main()
{
        ListNode* head = createList({1,2,3,4,5});
        int k = 3;

        cout<<"原链表: ";
        printList(head);
        head = reverKNodes(head,k);

        cout<<"反转前 "<<k<<" 个节点后的链表: ";
        printList(head);

        return 0;
}