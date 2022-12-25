#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int l, r;
    cin >> l >> r;
    if (l == 0 && r == 0) cout << "Not a moose";
    else cout << (l == r ? "Even" : "Odd") << ' ' << max(l, r) * 2;
}