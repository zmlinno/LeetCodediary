#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;
//1235
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		//使用哈希表来确保唯一性。
        unordered_set<int> set1(nums1.begin(), nums1.end());
        unordered_set<int> result;

        for (int num : nums2) {
            if (set1.count(num)) {
                result.insert(num); //插入到结果集合中，自动去重。
            }
        }

        return vector<int>(result.begin(), result.end());
    }
};

int main() {
    Solution solution;

    vector<int> nums1 = {1, 2, 2, 1};
    vector<int> nums2 = {2, 2};

    vector<int> result = solution.intersection(nums1, nums2);

    cout << "交集结果: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}