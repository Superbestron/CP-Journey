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
    vll a(n);
    for (auto& i : a) cin >> i;
    if (k % 2 == 1) {
        for (ll i : a) {
            if (i % 2 == 0) cout << i << ' ';
            else cout << i + k << ' ';
        }
    } else if (k == 2) {
        for (ll i : a) {
            if (i % 3 == 0) cout << i << ' ';
            else if (i % 3 == 1) {
                if (k % 3 == 1) cout << i + 2 * k << ' ';
                else cout << i + k << ' ';
            } else {
                if (k % 3 == 1) cout << i + k << ' ';
                else cout << i + 2 * k << ' ';
            }
        }
    } else {
        // need divisible by k - 1
        for (ll i : a) {
            ll r = i % (k - 1);
            ll m = (k - 1 - r) % (k - 1);
            ll tmp = i + m * k;
            cout << tmp << ' ';
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
}