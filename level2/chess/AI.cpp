#include "chess.h"
constexpr int D = 4;
struct node {
    int x, y, value;
    node(int a, int b, int c) : x(a), y(b), value(c) {}
};
bool operator<(const node& a, const node& b) {
    return a.value < b.value;
}
bool operator>(const node& a, const node& b) {
    return a.value > b.value;
}
int upd(int score) {
    if (score == 5) return inf;
    return max(0, score);
}
int valueo(int o) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            sum += upd(heng5(i, j, o));
            sum += upd(shu5(i, j, o));
            sum += upd(xie5_1(i, j, o));
            sum += upd(xie5_2(i, j, o));
        }
    }
    return sum;
}
int Value(int o) {
    return valueo(o) - valueo(o ^ 1);
}
int delta_value(int x, int y, int o, int op) {
    int delta = 0;
    for (int i = 0; i < 5; ++i) {
        if (y - i >= 1) delta -= upd(heng5(x, y - i, o)) - upd(heng5(x, y - i, o ^ 1));
        if (x - i >= 1) delta -= upd(shu5(x - i, y, o)) - upd(shu5(x - i, y, o ^ 1));
        if (x - i >= 1 && y - i >= 1) delta -= upd(xie5_1(x - i, y - i, o)) - upd(xie5_1(x - i, y - i, o ^ 1));
        if (x - i >= 1 && y + i <= n) delta -= upd(xie5_2(x - i, y + i, o)) - upd(xie5_2(x - i, y + i, o ^ 1));
    }
    chess[x][y] = op;
    for (int i = 0; i < 5; ++i) {
        if (y - i >= 1) delta += upd(heng5(x, y - i, o)) - upd(heng5(x, y - i, o ^ 1));
        if (x - i >= 1) delta += upd(shu5(x - i, y, o)) - upd(shu5(x - i, y, o ^ 1));
        if (x - i >= 1 && y - i >= 1) delta += upd(xie5_1(x - i, y - i, o)) - upd(xie5_1(x - i, y - i, o ^ 1));
        if (x - i >= 1 && y + i <= n) delta += upd(xie5_2(x - i, y + i, o)) - upd(xie5_2(x - i, y + i, o ^ 1));
    }
    chess[x][y] = -1;
    return delta;
}
node dfs(int d, int o, int valueo, int lst) {
    if (abs(valueo) >= inf) return node(-1, -1, valueo);
    if (d > D) return node(-1, -1, valueo);
    vector<node> vec;
    int op = o ^ (d & 1) ^ 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (chess[i][j] == -1) {
                vec.emplace_back(i, j, valueo + delta_value(i, j, o, op));
                // chess[i][j] = op;
                // assert(valueo + delta_value(i, j, o, op) == Value(o));
                // chess[i][j] = -1;
            }
        }
    }
    if (vec.empty()) return node(-1, -1, valueo);
    int len = min(20, ((int) vec.size() + 2) / 3);
    if (d % 2 == 1) {
        sort(all(vec), greater<>());
        node final_choice = node(-1, -1, INT_MIN);
        for (int i = 0; i < len; ++i) {
            int x = vec[i].x, y = vec[i].y;
            chess[x][y] = op;
            // assert(Value(o) == vec[i].value);
            final_choice = max(final_choice, node(x, y, dfs(d + 1, o, vec[i].value, final_choice.value).value));
            chess[x][y] = -1;
            // if (final_choice.value >= lst) return final_choice;
        }
        return final_choice;
    } else {
        sort(all(vec));
        node final_choice = node(-1, -1, INT_MAX);
        for (int i = 0; i < len; ++i) {
            int x = vec[i].x, y = vec[i].y;
            chess[x][y] = op;
            // assert(Value(o) == vec[i].value);
            final_choice = min(final_choice, node(x, y, dfs(d + 1, o, vec[i].value, final_choice.value).value));
            chess[x][y] = -1;
            // if (final_choice.value <= lst) return final_choice;
        }
        return final_choice;
    }
}
void AI_play(int o)
{
    node ans = dfs(1, o, Value(o), INT_MAX);
    cerr << "AI:" << ans.x << ' ' << ans.y << ' ' << ans.value << '\n';
    chess[ans.x][ans.y] = o;
}