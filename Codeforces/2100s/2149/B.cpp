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
    sort(a.begin(), a.end());
    int ans = 0;
    for (int i = 0; i < n / 2; i++) {
        ans = max(ans, a[2 * i + 1] - a[2 * i]);
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
