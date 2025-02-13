#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include"List.h"
using namespace std;

int main()
{
        // 创建链表 4 -> 5 -> 3 -> 1
        ListNode* head = new ListNode(4);
        head->next = new ListNode(5);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(1);

        int targetIndex = 1; //假如这是目标索引
        printNodeAtIndex1(head,targetIndex);
    
        cout << "链表各节点索引及值：" << endl;
        printListWithIndex(head);
    
        return 0;
}