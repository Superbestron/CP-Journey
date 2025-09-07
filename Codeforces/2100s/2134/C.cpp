#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

inline void solve() {
    cin >> n;
    vi a(n);
    for (int &i : a) cin >> i;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) continue;
        if (a[i] < a[i - 1]) {
            ans += a[i - 1] - a[i];
            a[i - 1] = a[i];
        }
        if (i + 1 != n) {
            if (a[i - 1] + a[i + 1] - a[i] > 0) {
                int extra = a[i - 1] + a[i + 1] - a[i];
                ans += extra;
                a[i + 1] -= extra;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
}
