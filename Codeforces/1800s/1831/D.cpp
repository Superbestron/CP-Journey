#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;
typedef vector<ii> vii;
typedef vector<ll> vll;

int t, n;

void solve() {
  cin >> n;
  vector<vi> mp(635, vi(n + 1));
  vll a(n), b(n);
  int limit = floor(sqrt(2 * n));
  ll ans = 0;
  for (ll &i : a) cin >> i;
  for (ll &i : b) cin >> i;
  for (int i = 0; i < n; i++) {
    if (a[i] <= limit) mp[a[i]][b[i]]++;
  }

  // find numbers which ai = aj (where i can == j)
  for (int i = 0; i < n; i++) {
    if (a[i] <= limit) {
      int num = a[i] * a[i] - b[i];
      if (num >= 1 && num <= n) ans += mp[a[i]][num];
    }
  }

  // account for pairs which consists of same indices (i == j)
  for (int i = 2; i <= limit; i += 2) ans -= mp[i][i * i / 2];
  ans >>= 1;

  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= limit && j < a[i] && j * a[i] <= 2 * n; j++) {
      int num = j * a[i] - b[i];
      if (num >= 1 && num <= n) ans += mp[j][num];
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
