#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m, a, b;

inline void solve() {
    cin >> n >> m;
    vii v(n);
    for (auto &[x, y] : v) cin >> x >> y;
    int pos = 0;
    int pts = 0;
    int prevTime = 0;
    for (int i = 0; i < n; i++) {
        auto &[x, y] = v[i];
        if ((pos ^ y) == 0) { // same
            int toAdd = (x - prevTime) / 2 * 2;
            pts += toAdd;
        } else {
            int toAdd = (x - prevTime - 1) / 2 * 2 + 1;
            pts += toAdd;
        }
        pos = y;
        prevTime = x;
    }
    cout << pts + m - prevTime << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
}
