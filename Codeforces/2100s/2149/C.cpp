#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

inline void solve() {
    cin >> n >> k;
    vi a(n);
    for (int &i : a) cin >> i;
    int ans = 0;
    unordered_set<int> s;
    for (int i = 0; i < n; i++) {
        if (a[i] < k) {
            s.insert(a[i]);
        } else if (a[i] == k) ans++;
    }
    cout << max(ans, k - (int)s.size()) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
}
