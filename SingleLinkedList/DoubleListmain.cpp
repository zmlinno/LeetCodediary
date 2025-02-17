#include<iostream>
#include"DoubleList.cpp"
using namespace std;
int main() {
        ListNode* list = ListCreate();
    
        // 尾插
        ListPushBack(list, 10);
        ListPushBack(list, 20);
        ListPushBack(list, 30);
        cout << "尾插 10, 20, 30: ";
        ListPrint(list);
    
        // 头插
        ListPushFront(list, 5);
        ListPushFront(list, 1);
        cout << "头插 5, 1: ";
        ListPrint(list);
    
        // 查找 20 并在前面插入 99
        ListNode* node20 = ListFind(list, 20);
        if (node20) {
            ListInsert(node20, 99);
            cout << "在 20 前插入 99: ";
            ListPrint(list);
        }
    
        // 删除 20
        if (node20) {
            ListErase(node20);
            cout << "删除 20: ";
            ListPrint(list);
        }
    
        // 头删
        ListPopFront(list);
        cout << "删除头节点: ";
        ListPrint(list);
    
        // 尾删
        ListPopBack(list);
        cout << "删除尾节点: ";
        ListPrint(list);
    
        // 释放链表
        ListDestroy(list);
    
        return 0;
    }