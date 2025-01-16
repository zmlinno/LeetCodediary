//
//  STL.hpp
//  C++
//
//  Created by 张木林 on 1/15/25.
//

#ifndef STL_hpp
#define STL_hpp

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class STLUtils {
public:
    // 打印 vector 内容
    template <typename T>
    static void printVector(const std::vector<T>& vec) {
        for (const T& v : vec) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    // 打印 set 内容
    template <typename T>
    static void printSet(const std::set<T>& s) {
        for (const T& v : s) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    
    //排序
    template <typename T>
    static void sortVector(std::vector<T>& vec) {
        std::sort(vec.begin(), vec.end());
    }

    // 打印 map 内容
    template <typename K, typename V>
    static void printMap(const std::map<K, V>& m) {
        for (const auto& pair : m) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    // 查找元素
    template <typename T>
    static bool findInVector(const std::vector<T>& vec, const T& value) {
        return std::find(vec.begin(), vec.end(), value) != vec.end();
    }

    // 二分查找
    template <typename T>
    static bool binarySearchInVector(const std::vector<T>& vec, const T& value) {
        return std::binary_search(vec.begin(), vec.end(), value);
    }
};
#endif /* STL_hpp */
