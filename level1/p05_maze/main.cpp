#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
constexpr int N = 15;
struct point {
    int x, y;
    point(){}
    point(int a, int b){x = a, y = b;}
    bool operator==(const point &a) const {
        return x == a.x && y == a.y;
    }
}Player, EN;
char Map[N][N];
void Build_Maze(int n)
{
    Player = point(n, 1), EN = point(1, n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            Map[i][j] = '.';
        }
    }
    // Map[5][5] = '*';
}
bool Move(point &p)
{
    while (!_kbhit());
    int c = _getch();
    if (c == 0 || c == 224) {
        point p_copy = p;
        switch (_getch()) {
            case 72: --p.x; break; // U
            case 80: ++p.x; break; // D
            case 75: --p.y; break; // L
            case 77: ++p.y; break; // R
        }
        if (Map[p.x][p.y] == '*') {
            p = p_copy;
            return false;
        }
        return true;
    }
    return false;
}
int main()
{
    int n = 10;
    Build_Maze(n);
    while (Player != EN) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (Player == point(i, j)) cout << "P";
                else if (EN == point(i, j)) cout << "E";
                else cout << Map[i][j];
            } cout << '\n';
        }
        cout << ". is the empty land and * is the Wall.\n";
        cout << "P is your position and E is exit.\n";
        // if (Move(Player)) system("cls");;
        // else cout << "Uh oh, you hit the wall. Please take the another way.\n";
    }
    cout << "Congratulations!\n";
    return 0;
}