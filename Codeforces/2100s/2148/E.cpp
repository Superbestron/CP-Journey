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
    map<int, int> m, needed, current;
    for (int &i : a) {
        cin >> i;
        m[i]++;
    }
    for (auto& [c, d] : m) {
        if (d % k != 0) {
            cout << "0\n";
            return;
        }
        needed[c] = d / k;
    }
    int size = 0;
    ll ans = 0;
    int msSize = n / k;
    for (int i = 0; i < n; i++) {
        int curr = a[i];
        if (size == msSize) {
            size--;
            current[a[i - msSize]]--; // remove
        }
        current[curr]++;
        size++;
        if (current[curr] > needed[curr] || (needed[curr] - current[curr] > (msSize - size))) {
            while (current[curr] > needed[curr]) {
                current[a[i - size + 1]]--; // remove
                size--;
            }
            ans += size;
        } else {
            ans += size;
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
