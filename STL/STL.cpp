//
//  STL.cpp
//  C++
//
//  Created by 张木林 on 1/15/25.
//

#include "STL.hpp"
#include<iostream>

int main() {
    // 示例 1: 操作 vector
    std::vector<int> myVector = {5, 3, 8, 1};
    STLUtils::printVector(myVector); // 打印原始 vector

    STLUtils::sortVector(myVector); // 排序 vector
    std::cout << "排序后的 vector: ";
    STLUtils::printVector(myVector);

    bool found = STLUtils::findInVector(myVector, 3); // 查找 3
    std::cout << (found ? "找到了 3" : "没找到 3") << std::endl;


    // 示例 2: 操作 set
    std::set<int> mySet = {4, 7, 1, 3};
    STLUtils::printSet(mySet); // 打印 set

    // 示例 3: 操作 map
    std::map<std::string, int> myMap = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 20}};
    STLUtils::printMap(myMap); // 打印 map

    // 示例 4: 二分查找 (需排序)
    bool binaryFound = STLUtils::binarySearchInVector(myVector, 8);
    std::cout << (binaryFound ? "通过二分查找找到了 8" : "通过二分查找没找到 8") << std::endl;

    return 0;
}


