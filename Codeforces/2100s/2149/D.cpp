#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;
string s;

inline void solve() {
    cin >> n >> s;
    ll a = 0, b = 0;
    vi pos_a, pos_b;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') pos_a.push_back(i);
        else pos_b.push_back(i);
    }

    if (!pos_a.empty()) {
        int pos = pos_a.size() / 2;
        for (int i = 0; i < pos_a.size(); i++) {
            a += abs(pos_a[pos] - pos_a[i]) - abs(pos - i);
        }
    }

    if (!pos_b.empty()) {
        int pos = pos_b.size() / 2;
        for (int i = 0; i < pos_b.size(); i++) {
            b += abs(pos_b[pos] - pos_b[i]) - abs(pos - i);
        }
    }

    cout << min(a, b) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        solve();
    }
}
