#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;

ll t, n, k, d;

void solve() {
  cin >> n >> k >> d;
  vll a(n), v(k);
  ll curr = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] == i + 1) curr++;
  }
  for (ll &i : v) cin >> i;
  // simulate first
  ll best_score = curr + (d - 1) / 2;
  // i is day
  for (int i = 0; i < min(2 * n, d - 1); i++) {
    curr = 0;
    for (int j = 0; j < v[i % v.size()]; j++) a[j]++;
    for (int j = 0; j < n; j++) {
      if (a[j] == j + 1) curr++;
    }
    best_score = max(best_score, curr + (d - 2 - i) / 2);
  }
  cout << best_score << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
