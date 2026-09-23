#include <iostream>
#include <ctime>
using namespace std;
constexpr int N = 1000;
bool not_prime[N + 1];
void sieve_primes(int n)
{
    for (int i = 2; i <= n; ++i) {
        if (not_prime[i]) continue;
        for (int j = i * i; j <= n; j += i) {
            not_prime[j] = 1;
        }
    }
}
void print_primes(int n)
{
    cout << "Primes: ";
    for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
            cout << i << ' ';
        }
    }
    cout << endl;
}
int main()
{
    sieve_primes(N);
    print_primes(N);
    cout << "Running time: " << (double) clock() / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}