#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
constexpr int N = 105;
struct point {
    int x, y;
    point(){x = y = 0;}
    point(int a, int b){x = a, y = b;}
    bool operator==(const point &a) const {
        return x == a.x && y == a.y;
    }
}Player;
char Map[N][N];
string map_name;
void Build_Maze(int n)
{
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= n + 1; ++j) {
            Map[i][j] = '#';
        }
    }
    int c1 = 0, c2 = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> Map[i][j];
            switch (Map[i][j]) {
                case 'P': Player = point(i, j); Map[i][j] = '.'; break;
                case 'X': ++c1; break;
                case 'O': ++c2; break;
                case '#': case '.': case '*': break;
                default: cout << "unexpected character:" << Map[i][j] << endl; exit(0);
            }
        }
    }
    if (c1 != c2) {
        cout << "box should be equal to the goal.";
        exit(0);
    }
    if (Player == point(0, 0)) {
        cout << "No player position.";
        exit(0);
    }
}
bool Move(point &p)
{
    while (!_kbhit());
    int c = _getch();
    if (c == 0 || c == 224) {
        int dx = 0, dy = 0;
        switch (_getch()) {
            case 72: dx = -1; break; // U
            case 80: dx = 1; break; // D
            case 75: dy = -1; break; // L
            case 77: dy = 1; break; // R
            default: return false;
        }
        int x = p.x + dx, y = p.y + dy;
        switch (Map[x][y]) {
            case '#':
                return false;
                break;
            case 'X':
                if (Map[x + dx][y + dy] == '.') {
                    Map[x + dx][y + dy] = 'X';
                    Map[x][y] = '.';
                    break;
                } else if (Map[x + dx][y + dy] == 'O') {
                    Map[x + dx][y + dy] = '*';
                    Map[x][y] = '.';
                    break;
                }
                return false;
            case '*':
                if (Map[x + dx][y + dy] == '.') {
                    Map[x + dx][y + dy] = 'X';
                    Map[x][y] = 'O';
                    break;
                } else if (Map[x + dx][y + dy] == 'O') {
                    Map[x + dx][y + dy] = '*';
                    Map[x][y] = 'O';
                    break;
                }
                return false;
            case 'O': case '.': break;
            default: return false;
        }
        Player = point(x, y);
        return true;
    }
    return false;
}
void init()
{
    cout << "Enter map name:";
    cin >> map_name;
    if (!freopen((map_name+".txt").c_str(), "r", stdin)) {
        cout << "cannot open file.\n";
        exit(0);
    }
}
int main()
{
    init();
    int n;
    cin >> n;
    Build_Maze(n);
    int cnt = 0;
    auto check = [&]() {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (Map[i][j] == 'X') {
                    return false;
                }
            }
        }
        return true;
    };
    while (!check()) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (Player == point(i, j)) cout << "P";
                else cout << Map[i][j];
            } cout << '\n';
        }
        cout << "----------------------\n";
        cout << ". is the empty land and # is the Wall.\n";
        cout << "P is your position.\n";
        cout << "X is the box and O is the goal.\n";
        cout << "* stands for that you matched it.\n";
        if (!Move(Player)) {
            cout << "Please try again.\n";
            while (!Move(Player));
        }
        ++cnt;
        system("cls");
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (Player == point(i, j)) cout << "P";
            else cout << Map[i][j];
        } cout << '\n';
    }
    cout << "Congratulations!\n";
    freopen((map_name+"_score.txt").c_str(), "w", stdout);
    cout << "Walk: " << cnt << endl;
    return 0;
}