#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

ll t, n, k, pb, ps;

inline void solve() {
  cin >> n >> k >> pb >> ps;
  pb--; ps--;
  vll p(n), a(n);
  for (ll &i : p) {
    cin >> i;
    i--;
  }
  for (ll &i : a) cin >> i;
  ll moves_b = k, moves_c = k;
  vi visited_b(n), visited_c(n);
  ll best_b = 0, sum_b = 0, best_c = 0, sum_c = 0;
  while (moves_b && !visited_b[pb]) {
    visited_b[pb] = true;
    best_b = max(best_b, sum_b + moves_b * a[pb]);
    sum_b += a[pb];
    moves_b--;
    pb = p[pb];
  }
  while (moves_c && !visited_c[ps]) {
    visited_c[ps] = true;
    best_c = max(best_c, sum_c + moves_c * a[ps]);
    sum_c += a[ps];
    moves_c--;
    ps = p[ps];
  }
//cout << best_b << ' ' << best_c << '\n';
  if (best_b > best_c) cout << "Bodya\n";
  else if (best_b == best_c) cout << "Draw\n";
  else cout << "Sasha\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
