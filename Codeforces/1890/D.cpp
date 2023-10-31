#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll tc, n, c;
  cin >> tc;
  while (tc--) {
    cin >> n >> c;
    bool can = true;
    vector<ll> v(n), s(n);
    for (ll &i : v) cin >> i;
    iota(s.begin(), s.end(), 1);
    sort(s.begin(), s.end(), [&](int x, int y) {
      return 1LL * c * x - v[x - 1] < 1LL * c * y - v[y - 1];
    });
    ll curr = v[0];
    for (int i = 0; i < n; i++) {
      if (s[i] == 1) continue;
      if (v[s[i] - 1] + curr < s[i] * c) {
        can = false;
        break;
      }
      curr += v[s[i] - 1];
    }
    if (can) cout << "Yes\n";
    else cout << "No\n";
  }
}