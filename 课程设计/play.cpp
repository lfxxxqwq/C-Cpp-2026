#include "chess.h"

#undef n
#define byte byte_
#include <windows.h>
#undef byte
#define n (15)

void AI_play(int, int);

// ==================== GUI 配置 ====================
static const int CELL      = 40;
static const int MARGIN    = 35;
static const int BOARD_PX  = CELL * (n - 1);
static const int WIN_W     = BOARD_PX + MARGIN * 2;
static const int WIN_H     = BOARD_PX + MARGIN * 2 + 40;

static const COLORREF COL_BG     = RGB(232, 192, 140);
static const COLORREF COL_LINE   = RGB(90, 50, 20);
static const COLORREF COL_BLACK  = RGB(25, 25, 25);
static const COLORREF COL_WHITE  = RGB(248, 248, 248);
static const COLORREF COL_LAST   = RGB(220, 30, 30);
static const COLORREF COL_STATUS = RGB(255, 255, 255);

// ==================== 全局状态 ====================
static HWND   g_hwnd        = NULL;
static bool   g_player_turn = false;
static int    g_click_x     = -1, g_click_y = -1;
static int    g_last_x      = -1, g_last_y  = -1;
static string g_status      = "";

// ==================== 坐标转换 ====================
static int px_of_col(int j) { return MARGIN + (j - 1) * CELL; }
static int py_of_row(int i) { return MARGIN + (i - 1) * CELL; }
static int col_of_px(int px) { return (int)lround((double)(px - MARGIN) / CELL) + 1; }
static int row_of_py(int py) { return (int)lround((double)(py - MARGIN) / CELL) + 1; }

// ==================== 绘制棋盘 ====================
static void draw_board(HDC hdc, int W, int H) {
    HBRUSH bg = CreateSolidBrush(COL_BG);
    RECT rc = {0, 0, W, H};
    FillRect(hdc, &rc, bg);
    DeleteObject(bg);

    HPEN line = CreatePen(PS_SOLID, 1, COL_LINE);
    HPEN oldPen = (HPEN)SelectObject(hdc, line);
    for (int k = 1; k <= n; ++k) {
        MoveToEx(hdc, px_of_col(1), py_of_row(k), NULL);
        LineTo  (hdc, px_of_col(n), py_of_row(k));
        MoveToEx(hdc, px_of_col(k), py_of_row(1), NULL);
        LineTo  (hdc, px_of_col(k), py_of_row(n));
    }
    SelectObject(hdc, oldPen);
    DeleteObject(line);

    HPEN border = CreatePen(PS_SOLID, 3, COL_LINE);
    oldPen = (HPEN)SelectObject(hdc, border);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Rectangle(hdc, px_of_col(1) - 3, py_of_row(1) - 3,
                   px_of_col(n) + 3, py_of_row(n) + 3);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(border);

    HBRUSH starBrush = CreateSolidBrush(COL_LINE);
    oldBrush = (HBRUSH)SelectObject(hdc, starBrush);
    int stars[][2] = {{4,4},{4,12},{12,4},{12,12},{8,8}};
    for (auto &s : stars) {
        int cx = px_of_col(s[1]), cy = py_of_row(s[0]);
        Ellipse(hdc, cx - 4, cy - 4, cx + 5, cy + 5);
    }
    SelectObject(hdc, oldBrush);
    DeleteObject(starBrush);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (chess[i][j] == -1) continue;
            int cx = px_of_col(j), cy = py_of_row(i);
            int r = CELL / 2 - 3;
            COLORREF col = chess[i][j] == 0 ? COL_BLACK : COL_WHITE;
            HBRUSH b = CreateSolidBrush(col);
            HPEN   p = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            HBRUSH ob = (HBRUSH)SelectObject(hdc, b);
            HPEN   op = (HPEN)SelectObject(hdc, p);
            Ellipse(hdc, cx - r, cy - r, cx + r, cy + r);
            SelectObject(hdc, ob);
            SelectObject(hdc, op);
            DeleteObject(b);
            DeleteObject(p);
        }
    }

    // 标记最后一步（玩家和 AI 都会标记）
    if (g_last_x != -1) {
        int cx = px_of_col(g_last_y), cy = py_of_row(g_last_x);
        HPEN rp = CreatePen(PS_SOLID, 2, COL_LAST);
        HPEN op = (HPEN)SelectObject(hdc, rp);
        HBRUSH ob = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
        int r = CELL / 2 - 1;
        Ellipse(hdc, cx - r, cy - r, cx + r, cy + r);
        SelectObject(hdc, op);
        SelectObject(hdc, ob);
        DeleteObject(rp);
    }
}

// ==================== 绘制状态栏 ====================
static void draw_status(HDC hdc, int W, int H) {
    HBRUSH b = CreateSolidBrush(COL_LINE);
    RECT rc = {0, H - 40, W, H};
    FillRect(hdc, &rc, b);
    DeleteObject(b);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, COL_STATUS);

    HFONT font = CreateFontA(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Microsoft YaHei");
    HFONT oldFont = (HFONT)SelectObject(hdc, font);

    RECT trc = {0, H - 40, W, H};
    DrawTextA(hdc, g_status.c_str(), -1, &trc,
              DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SelectObject(hdc, oldFont);
    DeleteObject(font);
}

// ==================== 窗口过程 ====================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_LBUTTONDOWN: {
        if (!g_player_turn) return 0;
        int px = LOWORD(lp), py = HIWORD(lp);
        int j = col_of_px(px), i = row_of_py(py);
        if (i < 1 || i > n || j < 1 || j > n) return 0;
        int cx = px_of_col(j), cy = py_of_row(i);
        int dx = px - cx, dy = py - cy;
        if (dx * dx + dy * dy > (CELL / 2) * (CELL / 2)) return 0;
        if (chess[i][j] != -1) return 0;
        g_click_x = i;
        g_click_y = j;
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HDC memDC  = CreateCompatibleDC(hdc);
        HBITMAP memBmp = CreateCompatibleBitmap(hdc, WIN_W, WIN_H);
        HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, memBmp);
        draw_board(memDC, WIN_W, WIN_H);
        draw_status(memDC, WIN_W, WIN_H);
        BitBlt(hdc, 0, 0, WIN_W, WIN_H, memDC, 0, 0, SRCCOPY);
        SelectObject(memDC, oldBmp);
        DeleteObject(memBmp);
        DeleteDC(memDC);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

// ==================== 创建窗口 ====================
static void create_window() {
    HINSTANCE hInst = GetModuleHandleA(NULL);
    WNDCLASSA wc = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "GomokuWnd";
    RegisterClassA(&wc);

    RECT rc = {0, 0, WIN_W, WIN_H};
    AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

    g_hwnd = CreateWindowA("GomokuWnd", "Gomoku (Five in a Row)",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,
        NULL, NULL, hInst, NULL);
    ShowWindow(g_hwnd, SW_SHOW);
    UpdateWindow(g_hwnd);
}

// ==================== 主流程接口 ====================
void print_chess() {
    if (g_hwnd) {
        InvalidateRect(g_hwnd, NULL, FALSE);
        UpdateWindow(g_hwnd);
    }
}

void player_play(int o, int step) {
    (void)step;
    g_player_turn = true;
    g_click_x = g_click_y = -1;
    g_status = "Your turn - click the board";
    print_chess();

    MSG msg;
    while (g_click_x == -1) {
        if (!GetMessage(&msg, NULL, 0, 0)) exit(0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    g_player_turn = false;
    chess[g_click_x][g_click_y] = o;
}

bool check(int o) {
    return valueo(o) >= inf;
}

void init() {
    memset(chess, -1, sizeof chess);
}

// ==================== 自动扫描更新最后落子 ====================
static int old_chess[n + 1][n + 1];

static void play_one_move(int o, int step, void (*play_func)(int, int)) {
    memcpy(old_chess, chess, sizeof chess);
    play_func(o, step); // 执行下棋（玩家或 AI）

    // 对比前后棋盘，自动找到最新下的那一颗棋
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (old_chess[i][j] != chess[i][j]) {
                g_last_x = i;
                g_last_y = j;
                return;
            }
        }
    }
}

// ==================== main ====================
int main() {
    init();
    create_window();

    int choice = MessageBoxA(g_hwnd,
        "Who goes first?\n\nYes = AI first\nNo  = Player first",
        "Gomoku", MB_YESNO | MB_ICONQUESTION);

    string black, white;
    void (*black_play)(int, int), (*white_play)(int, int);
    if (choice == IDYES) {
        black = "AI";     white = "Player";
        black_play = AI_play;     white_play = player_play;
    } else {
        black = "Player"; white = "AI";
        black_play = player_play; white_play = AI_play;
    }

    g_status = "Game start, " + black + " goes first";
    print_chess();

    for (int step = 1; step <= n * n; ++step) {
        if (step % 2 == 1) {
            if (black_play == AI_play) {
                g_status = "AI is thinking...";
                print_chess();
            }
            play_one_move(0, step, black_play);
            if (check(0)) {
                g_status = black + " wins!";
                print_chess();
                MessageBoxA(g_hwnd, (black + " wins!").c_str(), "Game over", MB_OK);
                goto wait_close;
            }
        } else {
            if (white_play == AI_play) {
                g_status = "AI is thinking...";
                print_chess();
            }
            play_one_move(1, step, white_play);
            if (check(1)) {
                g_status = white + " wins!";
                print_chess();
                MessageBoxA(g_hwnd, (white + " wins!").c_str(), "Game over", MB_OK);
                goto wait_close;
            }
        }
        print_chess();
    }

    g_status = "Tie!";
    print_chess();
    MessageBoxA(g_hwnd, "Tie!", "Game over", MB_OK);

wait_close: {
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return 0;
    }
}