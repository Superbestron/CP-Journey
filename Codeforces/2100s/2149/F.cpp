#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, h, d;

bool can(int rests) {
    int s = rests + 1;
    ll a = d / s, r = d % s;
    // r runs have length a + 1
    ll tmp1 = (a + 1) * (a + 2) / 2 * r;
    // s - r runs have length a
    ll tmp2 =  a * (a + 1) / 2 * (s - r);
    return (h + rests - 1 - tmp1 - tmp2) >= 0;
}

inline void solve() {
    cin >> h >> d;
    int ans = 0, l = 0, r = d;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (can(mid)) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    cout << ans + d << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
}
