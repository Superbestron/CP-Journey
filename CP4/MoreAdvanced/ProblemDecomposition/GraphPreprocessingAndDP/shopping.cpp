#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int n, m, s;
const ll INF = 1e18;
vector<vll> memo, dist;

ll dp(int u, int mask) { // mask = free coordinates
  if (mask == 0) return dist[u][0]; // close the tour
  ll &ans = memo[u][mask];
  if (ans != -1) return ans; // computed before
  ans = INF;
  int m = mask;
  while (m) { // up to O(n)
    int two_pow_v = LSOne(m); // but this is fast
    int v = __builtin_ctz(two_pow_v) + 1; // offset v by +1
    ans = min(ans, dist[u][v] + dp(v, mask ^ two_pow_v)); // keep the min
    m -= two_pow_v;
  }
  return ans;
}

inline void solve() {
  cin >> n >> m;
  vector<vii> AL(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    AL[u].emplace_back(v, w);
    AL[v].emplace_back(u, w);
  }
  cin >> s;
  memo.assign(1 + s, vll(1 << (1 + s - 1), -1));
  dist.assign(1 + s, vll(1 + s));
  vi locs(s);
  for (int &i : locs) cin >> i; // mapping of idx to loc
  for (int i = 0; i < s; i++) {
    priority_queue<ii, vii, greater<>> pq;
    vll dist2(n, INF);
    dist2[locs[i]] = 0;
    pq.emplace(0, locs[i]);
    while (!pq.empty()) {
      auto [d, u] = pq.top(); pq.pop();
      if (d > dist2[u]) continue;
      for (auto &[v, w] : AL[u]) {
        if (dist2[v] <= d + w) continue;
        dist2[v] = d + w;
        pq.emplace(dist2[v], v);
      }
    }
    for (int j = 0; j < s; j++) {
      dist[i + 1][j + 1] = dist2[locs[j]];
    }
    dist[i + 1][0] = dist[0][i + 1] = dist2[0];
  }
  cout << dp(0, (1 << s) - 1) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
