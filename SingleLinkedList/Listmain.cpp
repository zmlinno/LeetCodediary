#include<iostream>
using namespace std;
#include"SList.cpp"

int main() {
        SinglyLinkedList list;
    
        // 尾插法
        list.pushBack(1);
        list.pushBack(2);
        list.pushBack(3);
        list.pushBack(4);
        cout << "初始链表: ";
        list.printList();
    
        // 头插法
        list.pushFront(0);
        cout << "头插 0: ";
        list.printList();
    
        // 查找值为 2 的节点
        ListNode* node2 = list.find(2);
        if (node2) {
            list.insertAfter(node2, 99);
            cout << "在 2 之后插入 99: ";
            list.printList();
        }
    
        // 删除 2 之后的节点
        if (node2) {
            list.eraseAfter(node2);
            cout << "删除 2 之后的节点: ";
            list.printList();
        }
    
        // 头删
        list.popFront();
        cout << "删除头节点: ";
        list.printList();
    
        // 尾删
        list.popBack();
        cout << "删除尾节点: ";
        list.printList();
    
        // 释放链表
        list.destroy();
    
        return 0;
    }