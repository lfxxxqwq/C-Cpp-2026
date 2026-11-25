#include "chess.h"
#include <windows.h>
void AI_play(int, int);
bool mouse_get(int &x, int &y) {
    auto sqr = [](int x) {return x * x;};
    while (true) {
        if (!IsWindow(GetHWnd())) exit(0);
        ExMessage m;
        if (!peekmessage(&m, EM_MOUSE)) { Sleep(10); continue; }
        if (m.message != WM_LBUTTONDOWN) continue;
        int lx = m.x - 50;
        int ly = m.y - 50;
        int d = X / (n + 1);
        x = (lx + d / 2) / d;
        y = (ly + d / 2) / d;
        if (1 <= x && x <= n && 1 <= y && y <= n
         && sqr(x * d - lx) + sqr(y * d - ly) <= sqr(R)) return true;
    }
    return false;
}
void player_play(int o, int step) {
    int x, y;
    if (!mouse_get(x, y)) {
        cout << "Error. Please play chess again.\n";
        while (!mouse_get(x, y)) cin >> x >> y;
    }
    playo(x, y, o);
}
bool check(int o) {
    return valueo(o) >= inf;
}
void init() {
    memset(chess, -1, sizeof chess);
    initgraph(X + 100, Y + 150);
    setorigin(50, 50);
    setbkcolor(RGB(233, 205, 150));
    cleardevice();
    setcolor(RGB(107, 79, 42));
    setlinestyle(PS_SOLID, 3);
    for (int i : {0, n + 1}) {
        line(X / (n + 1) * i, 0, X / (n + 1) * i, Y);
        line(0, Y / (n + 1) * i, X, Y / (n + 1) * i);
    }
    setlinestyle(PS_SOLID, 1);
    for (int i = 1; i <= n; ++i) {
        line(X / (n + 1) * i, 0, X / (n + 1) * i, Y);
        line(0, Y / (n + 1) * i, X, Y / (n + 1) * i);
    }
    setfillcolor(RGB(107, 79, 42));
    for (int i : {3, 8, 13}) {
        for (int j : {3, 8, 13}) {
            solidcircle(X / (n + 1) * i, Y / (n + 1) * j, (i == 8 && j == 8) ? 5 : 3);  // 天元稍大
        }
    }
}
void holdWindow() {
    while (IsWindow(GetHWnd())) Sleep(50);
}
int main()
{
    init();
    string black, white;
    void (*black_play)(int, int), (*white_play)(int, int);
    int ret = MessageBoxW(NULL,
        L"请选择先手：\n是 = AI 先手，否 = 玩家先手",
        L"选择先手",
        MB_YESNO | MB_ICONQUESTION);
    int o = (ret == IDYES) ? 1 : 2;
    if (o == 1) {
        black = "AI";
        white = "player";
        black_play = AI_play;
        white_play = player_play;
    } else {
        black = "player";
        white = "AI";
        black_play = player_play;
        white_play = AI_play;
    }
    for (int step = 1; step <= n * n; ++step) {
        if (step % 2 == 1) {
            black_play(0, step);
            if (check(0)) {
                setbkmode(TRANSPARENT);
                settextstyle(20, 0, "SimHei");
                setcolor(RGB(107, 79, 42));
                outtextxy(50, 500, (black + " win.").c_str());
                holdWindow();
                return 0;
            }
        } else {
            white_play(1, step);
            if (check(1)) {
                setbkmode(TRANSPARENT);
                settextstyle(20, 0, "SimHei");
                setcolor(RGB(107, 79, 42));
                outtextxy(50, 500, (white + " win.").c_str());
                holdWindow();
                return 0;
            }
        }
    }
    setbkmode(TRANSPARENT);
    settextstyle(20, 0, "SimHei");
    setcolor(RGB(107, 79, 42));
    outtextxy(50, 500, "Tie");
    holdWindow();
    return 0;
    return 0;
}