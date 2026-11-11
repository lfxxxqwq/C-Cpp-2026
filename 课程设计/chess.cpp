#include "chess.h"
int chess[n + 1][n + 1];
// black first (0), white second (1).
int valuearray(vector<int>v, int o) {
    int p = 0, sum = 0;
    // for (int x : v) cerr << x << ' '; cerr << '\n';
    while (p < v.size()) {
        int q = p;
        while (q < v.size() && v[q] == o) ++q;
        int len = q - p, lopen = (p > 0 && v[p - 1] == -1), ropen = (q < v.size() && v[q] == -1);
        int open = lopen + ropen;
        if (len >= 5) {
            sum += 200000000;
        } else if (len == 4) {
            if (open == 2) {
                sum += 100000;
            } else if (open == 1) {
                sum += 10000;
            }
        } else if (len == 3) {
            if (open == 2) {
                sum += 8000;
            } else if (open == 1) {
                sum += 500;
            }
        } else if (len == 2) {
            if (open == 2) {
                sum += 300;
            } else if (open == 1) {
                sum += 50;
            }
        } else if (len == 1) {
            if (open == 2) {
                sum += 10;
            } else if (open == 1) {
                sum += 1;
            }
        }
        p = q + 1;
    }
    return sum;
}
int valueo(int o) {
    int value = 0;
    for (int i = 1; i <= n; ++i) {
        vector<int>v(n);
        for (int j = 1; j <= n; ++j) {
            v[j - 1] = chess[i][j];
        }
        value += valuearray(v, o);
    }
    for (int i = 1; i <= n; ++i) {
        vector<int>v(n);
        for (int j = 1; j <= n; ++j) {
            v[j - 1] = chess[j][i];
        }
        value += valuearray(v, o);
    }
    vector<int>v1[2 * (n + 1)], v2[2 * (n + 1)];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            v1[i + j].emplace_back(chess[i][j]);
            v2[i - j + n].emplace_back(chess[i][j]);
        }
    }
    for (int i = 0; i < 2 * (n + 1); ++i) {
        value += valuearray(v1[i], o);
        value += valuearray(v2[i], o);
    }
    return value;
}