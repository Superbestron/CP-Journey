#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, xa, ya, xb, yb, xc, yc;
    cin >> t;
    while (t--) {
        cin >> xa >> ya >> xb >> yb >> xc >> yc;
        int x = 0, y = 0;
        if (xb > xa && xa > xc || xc > xa && xa > xb) {
            x = 0;
        } else {
            x = max(min(xb, xc) - xa, xa - max(xb, xc));
        }
        if (yb > ya && ya > yc || yc > ya && ya > yb) {
            y = 0;
        } else {
            y = max(min(yb, yc) - ya, ya - max(yb, yc));
        }
        cout << x + y + 1 << '\n';
    }
}

