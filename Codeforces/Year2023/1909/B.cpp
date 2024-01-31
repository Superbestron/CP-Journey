#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef tuple<int, int> ii;

int t, n;

void solve() {
  cin >> n;
  vll a(n);
  bool all_odd = true, all_even = true;
  for (ll &i : a) {
    cin >> i;
    if (i % 2 == 0) all_odd = false;
    else all_even = false;
  }

  ll ans = 2;
  while (all_odd || all_even) {
    if (all_odd) {
      for (ll &i : a) i -= 1;
    } else {
      for (ll &i : a) i /= 2;
      ans *= 2;
    }
    all_odd = true;
    all_even = true;
    for (ll &i : a) {
      if (i % 2 == 0) all_odd = false;
      else all_even = false;
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