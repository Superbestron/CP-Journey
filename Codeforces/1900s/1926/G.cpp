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
  cin >> n;
  vector<vi> AL(n), memo(n, vi(3, 1e9));
  for (int i = 1; i <= n - 1; i++) {
    int v; cin >> v; v--;
    AL[v].push_back(i);
  }
  cin >> s;
  // 0 -> no mix, 1 -> P, 2 -> S
  auto dp = [&](auto &&f, int u) -> void {
    if (s[u] != 'S') memo[u][1] = 0;
    if (s[u] != 'P') memo[u][2] = 0;

    for (int v : AL[u]) {
      f(f, v);
      memo[u][1] += min({memo[v][1], memo[v][2] + 1, memo[v][0]});
      memo[u][2] += min({memo[v][2], memo[v][1] + 1, memo[v][0]});
      if (memo[u][0] < 1e9) memo[u][0] += memo[v][0];
    }

    if (s[u] != 'C') memo[u][0] = 1e9;
  };
  dp(dp, 0);
  cout << min({memo[0][0], memo[0][1], memo[0][2]}) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
