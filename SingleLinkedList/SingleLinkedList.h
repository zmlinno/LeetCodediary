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




//力扣160 相交链表
//找到两个链表的相交节点
ListNode* getIntersectionNode(ListNode* headA,ListNode* headB)
{
    if(!headA || headB) return nullptr;
    ListNode* pA = headA;
    ListNode* pB = headB;

    while(pA != pB)
    {
        pA = pA ? pA->next : headB;
        pB = pB ? pB->next : headA;
        //这个代码的意思就是，如果pA不是nullptr，就移动到pa->next
        //如果pa走完了headA，变成了null，就跳到headb开始便利
        //同理
    }

    return pA;
}



//力扣环形链表
bool hasCycle(ListNode* head)
{
    if(!head||!head->next) return false; //如果只有0或1个节点，直接返回

    ListNode* slow = head->next;
    ListNode* fast = head->next->next;

    while(fast && fast->next) //fast走到null
    {
        slow = slow->next; //慢指针走一步
        fast = fast->next->next; //快指针走两步

        if(slow == fast)
        {
            return true;
        }
    }
    return false;

}

//力扣21 合并两个有序链表
ListNode *mergeTwoList(ListNode* list1,ListNode* list2)
{
    ListNode *dummy = new ListNode(-1); //创建哨兵节点
    ListNode *tail = dummy; //维护最终链表的指针
    
    while(list1 && list2)
    {
        if(list1->val <= list2->val)
        {
            tail->next = list1;
            list1 = list1->next;
        }
        else
        {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next; //移动尾指针
    }
    //处理剩余元素
    if(list1)
    {
        tail->next = list1;
    }
    else
    {
        tail->next = list2;
    }
    return dummy->next;
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
