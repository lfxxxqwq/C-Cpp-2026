#include <iostream>
#include <windows.h>
using namespace std;
const int SLEEP = 50;
int N;
void Getlength()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hOut, &info);
	N = info.srWindow.Right - info.srWindow.Left + 1;
}
int main()
{
	Getlength();
	while (true) {
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
	}
	return 0;
}