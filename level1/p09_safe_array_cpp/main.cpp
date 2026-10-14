#include <bits/stdc++.h>
using namespace std;
template <typename T, int N>
class SafeArray {
    static_assert(N > 0, "N must be positive.");
private:
    T data[N];
public:
    T& operator[](int i) {
        if (i < 0 || i >= N) throw out_of_range("SafeArray index out of range.");
        return data[i];
    }
    const T& operator[](int i) const {
        if (i < 0 || i >= N) throw out_of_range("SafeArray index out of range.");
        return data[i];
    }
};
int main() {
    SafeArray<int, 5> a;
    for (int i = 0; i < 5; ++i) a[i] = i;
    for (int i = 0; i < 5; ++i) cout << a[i] << ' ';
    cout << '\n';

    SafeArray<double, 3> b;
    b[0] = 1.5; b[1] = 2.5; b[2] = 3.5;
    for (int i = 0; i < 3; ++i) cout << b[i] << ' ';
    cout << '\n';

    try {
        a[10] = 1;   // 10 >= 5, so report the error.
    } catch (const out_of_range& e) {
        cout << "caught: " << e.what() << '\n';
    }
    return 0;
}
