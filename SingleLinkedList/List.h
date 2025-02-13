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

//使用索引打印链表
void printListWithIndex(ListNode* head)
{
    ListNode* temp = head;
    int index = 0;

    while(temp)
    {
        cout<<"索引节点" <<index <<"-> 节点值: " <<temp->val <<" ";
        temp = temp->next;
        index++;
    }
}

void printNodeAtIndex1(ListNode* head,int targetIndex)
{
    ListNode *temp = head;
    int index = 0;

    while(temp)
    {
        if(index == targetIndex)
        {
            cout<<"索引 "<<index<<" 的节点数: "<<temp->val<<" ";
            return;
        }
        temp = temp->next;
        index++;
    }
    cout<<"索引 "<<targetIndex<<" 超出链表范围"<<" ";
}