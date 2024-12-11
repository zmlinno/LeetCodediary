#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		//ʹ�ù�ϣ����ȷ��Ψһ�ԡ�
        unordered_set<int> set1(nums1.begin(), nums1.end());
        unordered_set<int> result;

        for (int num : nums2) {
            if (set1.count(num)) {
                result.insert(num); //���뵽��������У��Զ�ȥ�ء�
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

    cout << "�������: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}