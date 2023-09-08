#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, val;
    cin >> t;
    while (t--) {
        int k = 0, ans = 0;
        cin >> n;
        vector<int> L(n);
        for (int i = 0; i < n; i++) {
            cin >> val;
            int pos = lower_bound(L.begin(), L.begin() + k, val) - L.begin();
            L[pos] = val;
            if (pos == 1) ans++;
            if (pos == k) {
                k = pos + 1;
            }
            int x = 5;
        }
        cout << ans << '\n';
    }
}