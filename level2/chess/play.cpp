#include "chess.h"
void AI_play(int o);
void player_play(int o) {
    int x, y;
    cin >> x >> y;
    if (!((1 <= x && x <= n) && (1 <= y && y <= n)) || chess[x][y] == -1) {
        cout << "Error. Please play chess again.\n";
        while (!((1 <= x && x <= n) && (1 <= y && y <= n)) || chess[x][y] == -1) cin >> x >> y;
    }
    chess[x][y] = o;
}
bool check(int o)
{
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (heng5(i, j, o) == 5) return true;
            if (shu5(i, j, o) == 5) return true;
            if (xie5_1(i, j, o) == 5) return true;
            if (xie5_2(i, j, o) == 5) return true;
        }
    }
    return false;
}
void print_chess() {
    system("cls");
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (chess[i][j] == 0) cout << "B";
            else if (chess[i][j] == 1) cout << "W";
            else cout << "*";
        } cout << '\n';
    }
}
void init()
{
    memset(chess, -1, sizeof chess);
}
int main()
{
    init();
    cout << "Who first? 1. AI. 2. player.\n";
    string black, white;
    void (*black_play)(int), (*white_play)(int);
    int o;
    cin >> o;
    if (o == 1) {
        black = "AI";
        white = "player";
        black_play = AI_play;
        white_play = player_play;
    } else if (o == 2) {
        black = "player";
        white = "AI";
        black_play = player_play;
        white_play = AI_play;
    } else {
        cout << "Error.\n";
        return 0;
    }
    print_chess();
    for (int step = 1; step <= n * n; ++step) {
        if (step % 2 == 1) {
            black_play(0);
            if (check(0)) {
                cout << black << " win!\n";
                return 0;
            }
        } else {
            white_play(1);
            if (check(1)) {
                cout << white << " win!\n";
                return 0;
            }
        }
        print_chess();
    }
    cout << "Tie.\n";
    return 0;
}