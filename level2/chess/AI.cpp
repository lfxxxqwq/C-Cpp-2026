#include "chess.h"
constexpr int D = 6;
// int Value(int o) // to be done.
// {
//     int sum = 0;
//     for (int i = 1; i <= n; ++i) {
//         for (int j = 1; j <= n; ++j) {
//             sum += max(0, heng5(i, j, o));
//             sum += max(0, shu5(i, j, o));
//             sum += max(0, xie5_1(i, j, o));
//             sum += max(0, xie5_2(i, j, o));
//         }
//     }
//     return sum;
// }
void AI_play(int o) // player play temporarily
{
    int x, y;
    cin >> x >> y;
    chess[x][y] = o;
}