#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, a, b;

inline void solve() {
    cin >> n >> a >> b;
    if (b >= a) {
        if ((n - b) % 2 == 0) cout << "YES\n";
        else cout << "NO\n";
    } else {
        if (((n - a) % 2 == 0) && (a - b) % 2 == 0) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
}
