#include "chess.h"
int chess[n + 1][n + 1];
// black first (0), white second (1).
int heng5(int x, int y, int o) { // (x, y) 开始横着连成
    if (y + 4 > n) return -1;
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        int t = chess[x][y + i];
        if (t == o) {
            ++sum;
        } else if (t == 1 - o) {
            return -1;
        }
    }
    return sum;
}
int shu5(int x, int y, int o) { // (x, y) 开始竖着连成
    if (x + 4 > n) return -1;
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        int t = chess[x + i][y];
        if (t == o) {
            ++sum;
        } else if (t == 1 - o) {
            return -1;
        }
    }
    return sum;
}
int xie5_1(int x, int y, int o) { // (x, y) 开始右下连成
    if (x + 4 > n || y + 4 > n) return -1;
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        int t = chess[x + i][y + i];
        if (t == o) {
            ++sum;
        } else if (t == 1 - o) {
            return -1;
        }
    }
    return sum;
}
int xie5_2(int x, int y, int o) { // (x, y) 开始左下连成
    if (x + 4 > n || y - 4 < 1) return -1;
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        int t = chess[x + i][y - i];
        if (t == o) {
            ++sum;
        } else if (t == 1 - o) {
            return -1;
        }
    }
    return sum;
}