#include <iostream>
using namespace std;
void hanoi(int n, char from, char to, char aux)
{
    if (n == 1) {
        cout << from << " -> " << to << '\n';
        return;
    }
    hanoi(n - 1, from, aux, to);
    cout << from << " -> " << to << '\n';
    hanoi(n - 1, aux, to, from);
}
int main()
{
    int n = 64;
    hanoi(n, 'A', 'C','B');
    return 0;
}
