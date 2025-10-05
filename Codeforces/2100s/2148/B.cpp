#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m, x, y;

inline void solve() {
    cin >> n >> m >> x >> y;
    vi a(n), b(m), c, d;
    int pt = 0;
    for (int &i : a) {
        cin >> i;
        if (i <= y) pt++;
    }
    for (int &i : b) {
        cin >> i;
        if (i <= x) pt++;
    }
    cout << pt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
}
