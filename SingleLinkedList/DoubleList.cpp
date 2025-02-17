#include<iostream>
#include"DoubleList.h"
using namespace std;

//定义双向链表节点
typedef int LTDataType;

// struct ListNode
// {
//         LTDataType _data;
//         ListNode* _next;
//         ListNode* _prev;

//         //构造函数
//         ListNode(LTDataType data = 0):_data(data),_next(nullptr),_prev(nullptr){}
// };


//创建循环双向链表
ListNode* ListCreate()
{
        ListNode* pHead = new ListNode();//头节点不存数据
        pHead->_next = pHead;
        pHead->_prev = pHead;
        return pHead;
}


//打印链表
void ListPrint(ListNode* pHead)
{
        ListNode* temp = pHead->_next;
        while(temp != pHead)
        {
                cout<<temp->_data<<"<->";
                temp = temp->_next;
        }
        cout<<"HEAD"<<endl;
}


//尾插
void ListPushBack(ListNode* pHead,LTDataType x)
{
        ListNode* newNode = new ListNode(x);
        ListNode* tail = pHead->_prev;

        tail->_next = newNode;
        newNode->_prev = tail;
        newNode->_next = pHead;
        pHead->_prev = newNode;
}

//双向链表头插
void ListPushFront(ListNode* pHead,LTDataType x)
{
        ListNode* newNode = new ListNode(x);
        ListNode* first = pHead->_next;

        pHead->_next = newNode;
        newNode->_prev = pHead;
        newNode->_next = first;
        first->_prev = newNode;
}

//尾删
void ListPopBack(ListNode* pHead)
{
        if(pHead->_next == pHead) return;//空链表

        ListNode* tail = pHead->_prev;
        ListNode* newTail = tail->_prev;

        newTail->_next = pHead;
        pHead->_prev = newTail;
        delete tail;
}

//头删
void ListPopFront(ListNode* pHead)
{
        if(pHead->_next == pHead)return; //空链表
        ListNode* first = pHead->_next;
        ListNode* newfirst = first->_next;

        pHead->_next = newfirst;
        newfirst->_prev = pHead;
        delete first;
}

//查找指定值
ListNode* ListFind(ListNode* pHead,LTDataType x)
{
        ListNode* temp = temp->_next;
        while(temp != pHead)
        {
                if(temp->_data == x) return temp;
                temp = temp->_next;
        }
        return nullptr;
}


//在pos之前插入
void ListInsert(ListNode* pos,LTDataType x)
{
        if(!pos)return;

        ListNode* newNode = new ListNode(x);
        ListNode* prev = pos->_next;

        prev->_next = newNode;
        newNode->_prev = prev;
        newNode->_next = pos;
        pos->_prev = newNode;
}

//删除pos位置的节点
void ListErase(ListNode* pos)
{
        if(!pos||pos->_next == pos)return;//不能删除头节点

        ListNode* prev = pos->_next;
        ListNode* next = pos->_next;

        prev->_next = next;
        next->_prev = prev;
        delete pos;
}


//释放链表
void ListDestroy(ListNode* pHead)
{
        ListNode* temp = pHead->_next;
        while(temp != pHead)
        {
                ListNode* next = temp->_next;
                delete temp;
                temp = next;
        }
        delete pHead;//删除头节点
}