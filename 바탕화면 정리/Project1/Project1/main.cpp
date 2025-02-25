#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<climits>
using namespace std;
很好
vector<int>solution(vector<string>wallpaper)
{
	int lux = INT_MAX, luy = INT_MAX, rdx = INT_MIN, rdy = INT_MIN;

	for (int i = 0; i < wallpaper.size(); i++)
	{
		for (int j = 0; j < wallpaper[i].size(); j++)
		{
			if (wallpaper[i][j] == '#')
			{
				lux = min(lux, i);
				luy = min(luy, j);
				rdx = max(rdx, i + 1);
				rdy = max(rdy, j + 1);
			}
		}
	}
	return { lux,luy,rdx,rdy };
}
// 主函数用于测试
int main() {
    vector<vector<string>> testCases = {
        {".#..", "..#.", "...#", "...."},
        {"..........", ".....#....", "......#...", "....###...", ".........."},
        {".##.......", "..#.......", ".......#..", ".......#.."},
        {".", "#"}
    };

    vector<vector<int>> expectedResults = {
        {0, 1, 3, 4},
        {1, 3, 5, 8},
        {0, 0, 4, 9},
        {1, 0, 2, 1}
    };

    bool allPassed = true;

    for (size_t i = 0; i < testCases.size(); ++i) {
        vector<int> result = solution(testCases[i]);
        cout << "Test Case " << i + 1 << ": ";
        cout << "Output: [" << result[0] << ", " << result[1] << ", "
            << result[2] << ", " << result[3] << "] ";
        cout << "Expected: [" << expectedResults[i][0] << ", "
            << expectedResults[i][1] << ", " << expectedResults[i][2] << ", "
            << expectedResults[i][3] << "] ";

        if (result == expectedResults[i]) {
            cout << "✔ Passed\n";
        }
        else {
            cout << "✘ Failed\n";
            allPassed = false;
        }
    }

    if (allPassed) {
        cout << "All test cases passed successfully!\n";
    }
    else {
        cout << "Some test cases failed. Please debug.\n";
    }

    return 0;
}