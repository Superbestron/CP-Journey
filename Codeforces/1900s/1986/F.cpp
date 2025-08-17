#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m;
map<ii, ii> mp;
vi visited;
vector<vi> AL;
vector<pair<int, int>> br;
vi disc, low;
int Time;

void dfsBR(int u, int p) {
  low[u] = disc[u] = ++Time;
  for (int& v : AL[u]) {
    if (v == p) continue; // we don't want to go back through the same path.
    // if we go back is because we found another way back
    if (!disc[v]) { // if V has not been discovered before
      dfsBR(v, u);  // recursive DFS call
      if (disc[u] < low[v]) // condition to find a bridge
        br.emplace_back(u, v);
      low[u] = min(low[u], low[v]); // low[v] might be an ancestor of u
    } else // if v was already discovered means that we found an ancestor
      low[u] = min(low[u], disc[v]); // finds the ancestor with the least discovery time
  }
}

int bfs(int u) {
  int sum = 0;
  for (int v : AL[u]) {
    if (visited[v]) continue;
    visited[v] = true;
    int nodes = bfs(v);
    mp[{min(u, v), max(u, v)}] = {min(nodes, n - nodes), max(nodes, n - nodes)};
    sum += nodes;
  }
  return sum + 1;
}

inline void solve() {
  cin >> n >> m;
  AL.assign(n, {});
  visited.assign(n, false);
  mp.clear();
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v; u--; v--;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }
  low.assign(n, 0);
  disc.assign(n, 0);
  br.clear();
  Time = 0;
  dfsBR(0, 0);
  visited[0] = true;
  bfs(0);
  ll ori = 1LL * n * (n - 1) / 2;
  ll ans = ori;
  for (auto &[u, v] : br) {
    auto &[n1, n2] = mp[{min(u, v), max(u, v)}];
    ll temp = 1LL * n1 * n2;
    ans = min(ans, ori - temp);
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
