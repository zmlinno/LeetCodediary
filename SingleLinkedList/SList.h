#include<iostream>
using namespace std;

class ListNode
{
public:
        int val;
        ListNode* next;

        //构造函数
        ListNode(int x):val(x),next(nullptr){}
};


//单链表类
class SinglyLinkedList
{
private:
        ListNode* head;//头指针

public:
        //构造函数
        SinglyLinkedList():head(nullptr){}

        //打印链表
        void printList();

        //头插
        void pushFront(int x);

        //尾插
        void pushBack(int x);

        //头删
        void popFront();

        //尾删
        void popBack();

        //查找节点
        ListNode* find(int x);

        //在指定节点之后插入
        void insertAfter(ListNode* pos,int x);

        //在指定节点之前插入
        void insertBefore(ListNode* pos,int x);

        //删除指定节点
        void eraseNode(ListNode* pos);

        //删除某个节点的下一个节点
        void eraseAfter(ListNode* pos);

        //释放链表
        void destroy();
};
