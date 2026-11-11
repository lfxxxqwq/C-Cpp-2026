#include "chess.h"
#undef n
#define byte byte_
#include <windows.h>
#undef byte
#define n (15)
void AI_play(int, int);
void player_play(int o, int step) {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    // 每次进入都重新开启鼠标输入，因为 print_chess 里的 system("cls")
    // 启动的 cmd 会重置控制台输入模式
    DWORD mode;
    GetConsoleMode(hIn, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hIn, mode);

    int x, y;
    while (true) {
        INPUT_RECORD ir;
        DWORD cnt = 0;
        ReadConsoleInput(hIn, &ir, 1, &cnt);

        if (ir.EventType != MOUSE_EVENT) continue;

        MOUSE_EVENT_RECORD &m = ir.Event.MouseEvent;
        if (m.dwEventFlags != 0) continue;                            // 只处理按下/抬起瞬间
        if (!(m.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) continue; // 只处理左键

        // print_chess 第 0 行就是棋盘第 1 行，每格单字符
        x = m.dwMousePosition.Y + 1;
        y = m.dwMousePosition.X + 1;

        if (!((1 <= x && x <= n) && (1 <= y && y <= n))) continue;  // 点在棋盘外
        if (chess[x][y] != -1) continue;                             // 已有棋子，重等

        break;
    }

    chess[x][y] = o;
}
bool check(int o) {
    return valueo(o) >= inf;
}
void print_chess() {
    system("cls");
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (chess[i][j] == 0) cout << "X";
            else if (chess[i][j] == 1) cout << "O";
            else cout << "_";
        } cout << '\n';
    }
}
void init() {
    memset(chess, -1, sizeof chess);
}
int main()
{
    init();
    cout << "Who first? 1. AI. 2. player.\n";
    string black, white;
    void (*black_play)(int, int), (*white_play)(int, int);
    // black = "black";
    // white = "white";
    // black_play = AI_play;
    // white_play = AI_play;
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
    print_chess(); // remeber to open it.
    for (int step = 1; step <= n * n; ++step) {
        cout << "step: " << step << '\n';
        if (step % 2 == 1) {
            black_play(0, step);
            if (check(0)) {
                print_chess();
                cout << black << " win!\n";
                return 0;
            }
        } else {
            white_play(1, step);
            if (check(1)) {
                print_chess();
                cout << white << " win!\n";
                return 0;
            }
        }
        print_chess();
    }
    cout << "Tie.\n";
    return 0;
}