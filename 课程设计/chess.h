#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define inf (100000000)
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
constexpr int n = 15, X = 480, Y = 480, R = 12;
extern int chess[n + 1][n + 1];
// black first (0), white second (1).
int valuearray(vector<int>v, int o);
int valueo(int o);
void playo(int x, int y, int o);
