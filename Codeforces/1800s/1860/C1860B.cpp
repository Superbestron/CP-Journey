#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, m, k, a1, ak;
    cin >> t;
    while (t--) {
        cin >> m >> k >> a1 >> ak;
        int left = m, ans = 0;
        if (ak != 0) {
            int ak_taken = min(ak, left / k);
            left -= ak_taken * k;
        }
        if (a1 != 0) {
            int a1_taken = min(a1, left);
            left -= a1_taken;
        }
        int ak_taken = left / k;
        left -= ak_taken * k;
        ans += ak_taken;
        if (left != 0) {
            // replace the a1 i took earlier with a k
            if ((k - left) <= a1) ans++;
            else ans += left;
        }
        cout << ans << '\n';
    }
}