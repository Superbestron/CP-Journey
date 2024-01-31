#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k, x;
    cin >> t;
    while (t--) {
        cin >> n >> k >> x;
        if (k == 1 && x == 1) {
            cout << "NO\n";
            continue;
        } else if (k >= 2 && x == 1) {
            if (n % 2 == 0) {
                cout << "YES\n";
                cout << n / 2 << '\n';
                for (int i = 0; i < n / 2; i++) cout << 2 << ' ';
                cout << '\n';
            } else {
                if (k == 2) {
                    cout << "NO\n";
                } else {
                    cout << "YES\n";
                    cout << (n - 3) / 2 + 1 << '\n';
                    for (int i = 0; i < (n - 3) / 2; i++) cout << 2 << ' ';
                    cout << 3 << ' ';
                    cout << '\n';
                }
            }
        } else {
            cout << "YES\n";
            cout << n << '\n';
            for (int i = 0; i < n; i++) cout << 1 << ' ';
            cout << '\n';
        }
    }
}

