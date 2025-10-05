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
    vi a(n), b;
    bool hasOdd = false;
    ll pt = 0;
    for (int &i : a) {
        cin >> i;
        if (i % 2 == 1) {
            hasOdd = true;
            b.push_back(i);
        } else {
            pt += i;
        }
    }
    sort(b.begin(), b.end(), greater<>());
    if (!hasOdd) cout << "0\n";
    else {
        for (int i = 0; i < (b.size() + 1) / 2; i++) {
            pt += b[i];
        }
        cout << pt << '\n';
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
