#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
const int N = 10, SLEEP = 50;
int main()
{
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j < i; ++j) cout << " ";
		cout << "a";
		Sleep(SLEEP);
		system("cls");
	}
	for (int i = N; i >= 1; --i) {
		for (int j = 1; j < i; ++j) cout << " ";
		cout << "a";
		Sleep(SLEEP);
		system("cls");
	}
	return 0;
}