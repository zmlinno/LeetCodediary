#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;


bool isFirstAndLastEqual(const string& str)
{
	if (str.empty())
	{
		return false;
	}
	return str.front() == str.back();
}
int main()
{
	string input;
	cout << "������һ���ַ�: " << endl;
	cin >> input;

	if (isFirstAndLastEqual(input))
	{
		cout << "��һ����ĸ�����һ����ĸ���" << endl;
	}
	else
	{
		cout << "�����" << endl;
	}
	return 0;
}