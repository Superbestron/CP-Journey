#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n; cin >> t;
    string s;
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (t--) {
        cin >> n >> s;
        int x = 0, y = 0;
        bool printed = false;
        for (char c : s) {
            if (c == 'U') {
                x += directions[0][0];
                y += directions[0][1];
            } else if (c == 'D') {
                x += directions[1][0];
                y += directions[1][1];
            } else if (c == 'L') {
                x += directions[3][0];
                y += directions[3][1];
            } else {
                x += directions[2][0];
                y += directions[2][1];
            }
            if (x == 1 && y == 1) {
                cout << "YES\n";
                printed = true;
                break;
            }
        }
        if (!printed) cout << "NO\n";
    }
}
