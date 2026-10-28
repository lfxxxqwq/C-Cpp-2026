#include <bits/stdc++.h>
using namespace std;
#define n (15)
extern int chess[n + 1][n + 1];
// black first (0), white second (1).
int heng5(int x, int y, int o); // (x, y) 开始横着连成
int shu5(int x, int y, int o); // (x, y) 开始竖着连成
int xie5_1(int x, int y, int o); // (x, y) 开始右下连成
int xie5_2(int x, int y, int o); // (x, y) 开始左下连成