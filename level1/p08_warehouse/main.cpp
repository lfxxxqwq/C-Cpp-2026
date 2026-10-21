#include <bits/stdc++.h>
using namespace std;
map<string, int>mp;
void read()
{
    ifstream fin("warehouse.txt");
    if (!fin) return; // empty warehouse at first.
    int n;
    if (!(fin >> n)) return; // empty warehouse at first.
    for (int i = 1; i <= n; ++i) {
        string name;
        int cnt;
        fin >> name >> cnt;
        mp[name] = cnt;
    }
}
void save()
{
    ofstream fout("warehouse.txt");
    if (!fout) {cout << "save failed."; return;}
    fout << mp.size() << '\n';
    for (auto [name, cnt] : mp) {
        fout << name << ' ' << cnt << '\n';
    }
}
int menu()
{
    system("cls");
    cout << "1. show the list.\n";
    cout << "2. enter some ware.\n";
    cout << "3. take out some ware.\n";
    cout << "4. exit\n";
    string op;
    if (!(cin >> op)) { // EOF
        if (cin.eof()) return -2;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    if (op.size() > 1) return -1;
    switch (op[0]) {
        case '1': return 1; break;
        case '2': return 2; break;
        case '3': return 3; break;
        case '4': return 4; break;
        default: return -1;
    }
}
int main() {
    read();
    while (true) {
        int op = -1;
        do {
            op = menu();
            if (op == -2) { save(); return 0; } // EOF
        } while (op == -1);
        system("cls");
        string name;
        int cnt;
        switch (op) {
            case 1:
                for (auto [name, cnt] : mp) {
                    cout << name << ':' << cnt << '\n';
                }
                break;
            case 2:
                if (!(cin >> name >> cnt)) {
                    if (cin.eof()) { save(); return 0; } // EOF
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "invalid input\n";
                    break;
                }
                if (cnt <= 0) {cout << "the number should be positive." << endl; break; }
                mp[name] += cnt;
                cout << name << " number: " << mp[name] << '\n';
                break;
            case 3:
                if (!(cin >> name >> cnt)) {
                    if (cin.eof()) { save(); return 0; } // EOF
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "invalid input\n";
                    break;
                }
                if (cnt <= 0) {cout << "the number should be positive." << endl; break; }
                if (mp[name] < cnt) {
                    cout << "There isn't enough " << name << ".\n";
                } else {
                    mp[name] -= cnt;
                }
                cout << name << " number: " << mp[name] << '\n';
                if (mp[name] == 0) mp.erase(name);
                break;
            case 4: save(); exit(0);
            default: break;
        }
        if (!cin.eof()) system("pause"); // EOF
    }
    return 0;
}