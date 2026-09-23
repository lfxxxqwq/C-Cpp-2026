#include <iostream>
using namespace std;
bool isp(long long x)
{
    if (x == 1) return false;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}
int main()
{
    long long n;
    cin >> n;
    if (isp(n)) {
        cout << n << " is a prime.\n";
    } else {
        cout << n << " is not a prime.\n";
    }
    return 0;
}