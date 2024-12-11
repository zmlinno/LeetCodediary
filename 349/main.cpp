#include<iostream>
#include<unordered_set>
#include<vector>
using namespace std;

int main()
{
    vector<int>nums = {1,2,3,4};
    unordered_set<int>set1(nums.begin(),nums.end());
    unordered_set<int>result;

    for(int sum : set1)
    {
        cout<<"ºÏ¼¯ÊÇ:"<<sum<<" ";
    }
    cout<<endl;
    return 0;
}