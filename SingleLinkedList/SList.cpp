#include<iostream>
using namespace std;
#include"SList.h"

//打印链表
void SinglyLinkedList::printList()
{
        ListNode* temp = head;
        while(temp)
        {
                cout<<temp->val<<" ";
                temp = temp->next;
        }
        cout<<"NULL"<<endl;
}


//头插法
void SinglyLinkedList::pushFront(int x)
{
        ListNode* newNode = new ListNode(x);
        newNode->next = head;
        head = newNode;
}

//尾插
void SinglyLinkedList::pushBack(int x)
{
        ListNode* newNode = new ListNode(x);
        if(!head)
        {
                head = newNode;
                return;
        }

        ListNode* temp = head;
        while(temp->next)
        {
                temp = temp->next;
        }
        temp->next = newNode;
}


//头删法
void SinglyLinkedList::popFront()
{
        if(!head)return;

        ListNode* temp = head;
        head = head->next;
        delete temp;
}

//尾删
void SinglyLinkedList::popBack()
{
        if(!head)return;
        if(!head->next)
        {
                delete head;
                head = nullptr;
                return;
        }

        ListNode* prev = nullptr;
        ListNode* curr = head;
        while(curr->next)
        {
                prev = curr;
                curr = curr->next;
        }
        prev->next = nullptr;
        delete curr;
}

//查找节点
ListNode* SinglyLinkedList::find(int x)
{
        ListNode* temp = head;
        while(temp)
        {
                if(temp->val == x)return temp;
                temp = temp->next;
        }
        return nullptr;
}

//在pos之后插入
void SinglyLinkedList::insertAfter(ListNode* pos,int x)
{
        if(!pos)return;

        ListNode* newNode = new ListNode(x);
        newNode->next = pos->next;
        pos->next = newNode;
}

//在pos之前插入
void SinglyLinkedList::insertBefore(ListNode* pos,int x)
{
        if(!head||head == pos)
        {
                pushFront(x);
                return;
        }
        ListNode* temp = head;
        while(temp->next&&temp->next != pos)
        {
                temp = temp->next;
        }
        if(temp->next)
        {
                ListNode* newNode = new ListNode(x);
                newNode->next = temp->next;
                temp->next = newNode;
        }

}


//删除指定节点
void SinglyLinkedList::eraseNode(ListNode* pos)
{
        if(!head||!pos)return;

        if(head == pos)
        {
                popFront();
                return;
        }
        ListNode* temp = head;
        while(temp->next&&temp->next != pos)
        {
                temp = temp->next;
        }
        if(temp->next)
        {
                temp->next = pos->next;
                delete pos;
        }
}

//删除pos之后的节点
void SinglyLinkedList::eraseAfter(ListNode* pos)
{
        if(!pos || !(pos->next))return;

        ListNode* temp = pos->next;
        pos->next = temp->next;
        delete temp;
}

//释放整个链表
void SinglyLinkedList::destroy()
{
        ListNode* temp;
        while(head)
        {
                temp = head;
                head = head->next;
                delete temp;
        }
}