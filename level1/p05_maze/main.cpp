#include <iostream>
#include <windows.h>
#include <conio.h>
#include <random>
using namespace std;
constexpr int N = 15;
struct point {
    int x, y;
    point(){}
    point(int a, int b){x = a, y = b;}
    bool operator==(const point &a) const {
        return x == a.x && y == a.y;
    }
}Player, END;
char Map[N][N];
mt19937 gen(time(0));
void Build_Maze(int n)
{
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= n + 1; ++j) {
            Map[i][j] = '#';
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            Map[i][j] = gen() % 2 ? '#' : '.';
        }
    }
    Player = point(n, 1), END = point(1, n);
    int x = n, y = 1;
    Map[x][y] = '.';
    for (int i = 1; i <= 2 * (n - 1); ++i) { //(n, 1) -> (1, n)
        if ((gen() % 2 && x > 1) || y >= n) {
            Map[--x][y] = '.';
        } else {
            Map[x][++y] = '.';
        }
    }
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
            default: return false;
        }
        if (Map[p.x][p.y] == '#') {
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
    while (Player != END) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (Player == point(i, j)) cout << "P";
                else if (END == point(i, j)) cout << "E";
                else cout << Map[i][j];
            } cout << '\n';
        }
        cout << "----------------------\n";
        cout << ". is the empty land and # is the Wall.\n";
        cout << "P is your position and E is exit.\n";
        if (!Move(Player)) {
            cout << "Please try again.\n";
            while (!Move(Player));
        }
        system("cls");
    }
    cout << "Congratulations!\n";
    return 0;
}