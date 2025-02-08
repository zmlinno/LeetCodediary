//删除排序链表中的重复元素2
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
//这是关于链表的反转和删除倒数N个节点
//关于如何找到尾节点
//比如说1-2-3-4-5
struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x):val(x),next(nullptr){}

};

struct LinkedList
{
    ListNode* head;
    ListNode* tail; //维护tail指针，直接指向尾节点
    LinkedList():head(nullptr),tail(nullptr){}

    //插入新节点，并更新tail指针
    void insert(int value)
    {
        ListNode* newNode = new ListNode(value);
        if(!head)
        {
            head = newNode;
            tail = newNode; //第一个节点即是尾节点
        }
        else
        {
            tail->next = newNode; //连接新节点
            tail = newNode; //更新tail指针
        }
    }

    //打印链表
    void printList()
    {
        ListNode* temp = head;
        while(temp)
        {
            cout<<temp->val<<" ->";
            temp = temp->next;
        }
        cout<<"Nullptr"<<endl;
    }
};

//返回链表的尾节点值
int findTailValue(ListNode* head)
{
    if(!head) return -1; //处理空链表，返回-1表示无效
    while(head->next)
    {
        head = head->next; //遍历到最后一个节点
    }
    return head->val; //返回尾节点的值
}

int main() {
    // // 创建链表 1 -> 2 -> 3 -> 4 -> 5 -> 6
    // ListNode* head = new ListNode(1);
    // head->next = new ListNode(2);
    // head->next->next = new ListNode(3);
    // head->next->next->next = new ListNode(4);
    // head->next->next->next->next = new ListNode(5);
    // head->next->next->next->next->next = new ListNode(6);

    // // 调用 findTailValue 获取尾节点的值
    // int tailValue = findTailValue(head);
    
    // // 输出结果
    // cout << "尾节点的值是: " << tailValue << endl;

    // return 0;

    LinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);

    list.printList();

    //输出头节点和尾节点的值
    cout<<"头节点的值: "<<list.head->val<<endl;
    cout<<"尾节点的值: "<<list.tail->val<<endl;

    return 0;
}
