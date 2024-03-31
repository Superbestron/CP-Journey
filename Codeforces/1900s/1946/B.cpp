#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;
const int MOD = 1e9 + 7;

void solve() {
  cin >> n >> k;
  vi a(n);
  for (int &i : a) cin >> i;
  ll sum = 0, best = 0, l = 0;
  ii range = {-1, -1};
  for (int i = 0; i < n; i++) {
    if (sum + a[i] < 0) {
      sum = 0;
      l = i + 1;
    } else {
      sum += a[i];
      if (sum > best) {
        best = sum;
        range = {l, i};
      }
    }
  }
  ll ans = best;
  for (int i = 0; i < k; i++) {
    ans = (ans * 2) % MOD;
  }
  for (int i = 0; i < n; i++) {
    if (i >= range.first && i <= range.second) continue;
    ans = (ans + a[i] + MOD) % MOD;
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
