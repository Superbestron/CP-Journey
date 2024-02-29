#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

ll t, n, b, x;

ll count_pairs(int cnt, int s) {
  ll rem = cnt % s;
  ll div = cnt / s;
  ll div_add_1 = div + 1;
  return (rem * (cnt - div_add_1) * div_add_1 + (s - rem) * (cnt - div) * div) / 2;
}

void solve() {
  cin >> n >> b >> x;
  vll a(n);
  ll squads = 0;
  for (ll &i : a) {
    cin >> i;
    squads = max(squads, i);
  }
  vll pair(squads + 1), mx(squads + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= a[i]; j++) {
//      cout << count_pairs(a[i], j) << '\n';
      pair[j] += count_pairs(a[i], j);
    }
    mx[a[i]] += count_pairs(a[i], a[i]);
//    cout << '\n';
  }

  ll ans = 0, extra = 0;
  for (int i = 1; i <= squads; i++) {
    ans = max(ans, b * (pair[i] + extra) - x * (i - 1));
    // Because for squads > ci, strength is always same when squads = ci,
    // this is a elegant way to represent the extra factor without actually
    // populating pair
    extra += mx[i];
  }
  cout << ans << '\n';
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
