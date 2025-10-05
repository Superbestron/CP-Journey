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
    int ans = 0, cnt = 0, min_num = INT_MAX;
    for (int &i : a) cin >> i;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) ans++;
        else if (a[i] == -1) {
            cnt++;
        }
        min_num = min(min_num, a[i]);
    }
    cout << ans + (cnt % 2) * 2  << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
}
