#include "chess.h"
constexpr int D = 6;
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
int Value(int o) {
    return valueo(o) - valueo(o ^ 1);
}
int delta_value(int x, int y, int o, int op) {
    auto calc = [&](int o) {
        int delta = 0;
        for (int i : {x}) {
            int l = max(1, y - 5), r = min(n, y + 5);
            vector<int>v(r - l + 1);
            for (int j = l; j <= r; ++j) {
                v[j - l] = chess[i][j];
            }
            delta += valuearray(v, o);
        }
        for (int i : {y}) {
            int l = max(1, x - 5), r = min(n, x + 5);
            vector<int>v(r - l + 1);
            for (int j = l; j <= r; ++j) {
                v[j - l] = chess[j][i];
            }
            delta += valuearray(v, o);
        }
        vector<int>v1, v2;
        for (int i = 1; i <= n; ++i) {
            if (1 <= x + y - i && x + y - i <= n) v1.emplace_back(chess[i][x + y - i]);
            if (1 <= i - x + y && i - x + y <= n) v2.emplace_back(chess[i][i - x + y]);
        }
        delta += valuearray(v1, o);
        delta += valuearray(v2, o);
        return delta;
    };
    int delta = 0;
    delta -= calc(o) - calc(o ^ 1);
    chess[x][y] = op;
    delta += calc(o) - calc(o ^ 1);
    chess[x][y] = -1;
    return delta;
}
node dfs(int d, int o, int value_o, int lst) {
    if (abs(value_o) >= inf) return node(-1, -1, value_o > 0 ? inf : -inf);
    if (d > D) return node(-1, -1, value_o);
    vector<node> vec;
    auto ok = [](int x, int y) {
        for (int i = max(1, x - 2); i <= min(n, x + 2); ++i) {
            for (int j = max(1, y - 2); j <= min(n, y + 2); ++j) {
                if (chess[i][j] != -1) {
                    return true;
                }
            }
        }
        return false;
    };
    int op = o ^ (d & 1) ^ 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (chess[i][j] == -1) {
                if (!ok(i, j)) continue;
                vec.emplace_back(i, j, value_o + delta_value(i, j, o, op));
                chess[i][j] = op;
                // assert(vec.back().value == Value(o));
                chess[i][j] = -1;
            }
        }
    }
    if (vec.empty()) return node(-1, -1, value_o);
    int len = min(50, (int) (vec.size() + 1) / 2);
    if (d % 2 == 1) {
        sort(all(vec), greater<>());
        node final_choice = node(-1, -1, INT_MIN);
        for (int i = 0; i < len; ++i) {
            int x = vec[i].x, y = vec[i].y;
            chess[x][y] = op;
            // assert(Value(o) == vec[i].value);
            final_choice = max(final_choice, node(x, y, dfs(d + 1, o, vec[i].value, final_choice.value).value));
            chess[x][y] = -1;
            if (final_choice.value >= lst) return final_choice;
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
            if (final_choice.value <= lst) return final_choice;
        }
        return final_choice;
    }
}
void AI_play(int o, int step)
{
    node ans = step == 1 ? node((n + 1) / 2, (n + 1) / 2, 0) : dfs(1, o, Value(o), INT_MAX);
    chess[ans.x][ans.y] = o;
    cerr << "AI:" << ans.x << ' ' << ans.y << ' ' << ans.value << ' ' << Value(o) << "<-val\n";
    cerr << valueo(o) << ' ' << valueo(o ^ 1) << endl;
}