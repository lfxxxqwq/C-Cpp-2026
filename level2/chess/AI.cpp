#include "chess.h"
constexpr int D = 3;
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
int value(int o)
{
    auto upd = [](int score) {
        if (score == 5) return inf;
        return max(0, score);
    };
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
    return value(o) - value(o ^ 1);
}
node dfs(int d, int o)
{
    if (Value(o) >= inf) return node(-1, -1, Value(o));
    if (d > D) return node(-1, -1, Value(o));
    vector<node> vec;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (chess[i][j] == -1) {
                chess[i][j] = o ^ (d & 1) ^ 1;
                vec.emplace_back(i, j, Value(o));
                chess[i][j] = -1;
            }
        }
    }
    if (vec.empty()) return node(-1, -1, Value(o));
    int len = min(20, ((int) vec.size() + 2) / 3);
    if (d % 2 == 1) {
        sort(all(vec), greater<>());
        node final_choice = node(-1, -1, -1);
        for (int i = 0; i < len; ++i) {
            int x = vec[i].x, y = vec[i].y;
            chess[x][y] = o;
            final_choice = max(final_choice, node(x, y, dfs(d + 1, o).value));
            chess[x][y] = -1;
        }
        return final_choice;
    } else {
        sort(all(vec));
        node final_choice = {-1, -1, inf};
        for (int i = 0; i < len; ++i) {
            int x = vec[i].x, y = vec[i].y;
            chess[x][y] = o;
            final_choice = min(final_choice, node(x, y, dfs(d + 1, o).value));
            chess[x][y] = -1;
        }
        return final_choice;
    }
}
void AI_play(int o)
{
    node ans = dfs(1, o);
    cerr << "AI:" << ans.x << ' ' << ans.y << '\n';
    chess[ans.x][ans.y] = o;
}