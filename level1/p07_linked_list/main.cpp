#include <bits/stdc++.h>
using namespace std;
constexpr int n = 7;
int a[n] = {0, 1, 2, 3, 4, 5, 6}; // you can revise n and a[] to test it.
struct Node {
    int value, id;
    Node* next;
    Node() {value = 0; id = 0; next = nullptr;}
};
Node* head = nullptr;
void print(Node* p) {
    if (p == nullptr) return;
    cout << p -> value << ' ';
    print(p -> next);
}
Node* reverse(Node* p) {
    if (p == nullptr) return nullptr;
    if (p -> next == nullptr) return p;
    Node *q = reverse(p -> next);
    (p -> next) -> next = p;
    p -> next = nullptr;
    return q;
}
Node* find5(Node* p) {
    if (p == nullptr) return nullptr;
    if (p -> value == 5) return p;
    return find5(p -> next);
}
void del(Node* p) {
    if (p == nullptr) return;
    del(p -> next);
    delete p;
}
int main() {
    Node* p = nullptr;
    if (n > 0) {
        head = new Node();
        p = head;
    }
    for (int i = 0; i < n; ++i) {
        p -> value = a[i];
        if (i < n - 1) {
            p -> next = new Node();
            p = p -> next;
        }
    }
    print(head), cout << endl;
    head = reverse(head);
    p = head;
    for (int i = 0; i < n; ++i) {
        p -> id = i;
        p = p -> next;
    }
    p = find5(head);
    if (p != nullptr) cout << p -> id << endl;
    else cout << -1 << endl;
    if (p == nullptr) cout << -1 << endl;
    else {
        p = find5(p -> next);
        if (p != nullptr) cout << p -> id << endl;
        else cout << -1 << endl;
    }
    del(head);
    return 0;
}