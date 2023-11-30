#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n;

inline void solve() {
  cin >> n;
  vector<int> v(n + 1);
  vector<ll> memo(n + 1);
  vector<bool> vis(n + 1);
  unordered_map<int, int> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
    m[v[i]]++;
  }
  for (int i = n; i; i--) {
    for (int j = i; j <= n; j += i) {
      memo[i] += m[j];  // add counts of numbers that divisible by i
      if (m[i]) vis[j] = true;
    }
    memo[i] = memo[i] * (memo[i] - 1) / 2;
    for (int j = i + i; j <= n; j += i) {
      memo[i] -= memo[j];
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += memo[i] * !vis[i];
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