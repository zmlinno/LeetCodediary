#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
//添加点别的东西 。
//ㅓㅑㅁ야ㅜㅁ
int main()
{
    vector<int>matrix = {11,2,3,10,22};
    bool isAscending = is_sorted(matrix.begin(),matrix.end());

    if(isAscending)
    {
        cout<<"True"<<endl;
    }
    else
    {
        cout<<"False"<<endl;
    }
    return 0;
}
