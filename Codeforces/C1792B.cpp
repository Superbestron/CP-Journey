#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long t, a1, a2, a3, a4; cin >> t;
    while (t--) {
        cin >> a1 >> a2 >> a3 >> a4;
        long long curr = 0;
        if (a1 != 0) {
            int minus = min(a2, a3);
            curr += a1 + 2 * minus;
            a3 -= minus;
            a2 -= minus;
        }
        if (a1 != 0 && a2 != 0) {
            int minus = min(a1, a2);
            curr += minus; a1 -= minus;
            a2 -= minus;
        }
        if (a1 != 0 && a3 != 0) {
            int minus = min(a1, a3);
            curr += minus; a1 -= minus;
            a3 -= minus;
        }
        if (a1 != 0 && a4 != 0) {
            curr += min(a1, a4); a4 -= min(a1, a4);
        }
        if (a2 != 0 || a3 != 0 || a4 != 0) curr++;
        cout << curr << '\n';
    }
}
