#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

int main()
{
    vector<int>number = {1,2,3,4,5};
    reverse(number.begin(),number.end());
    for(auto Number:number)
    {
        cout<<Number<<endl;

    }
    
    cout<<endl;
    return 0;
}