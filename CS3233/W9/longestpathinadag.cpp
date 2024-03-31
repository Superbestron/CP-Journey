#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int v, e;
vi dist;
vector<vi> AL;

void dfs(int u) {
  dist[u] = 1;
  for (int v : AL[u]) {
    if (dist[v] == -1) dfs(v);
    dist[u] = max(dist[u], 1 + dist[v]);
  }
}

void get_output(int u) {
  for (int v : AL[u]) {
    if (dist[u] == dist[v] + 1) {
      cout << v + 1 << ' ';
      return get_output(v);
    }
  }
}

inline void solve() {
  cin >> v >> e;
  AL.assign(v, {});
  dist.assign(v, -1);
  set<ii> s;
  for (int i = 0; i < e; i++) {
    int l, r; cin >> l >> r;
    l--; r--;
    if (s.count({l, r})) continue;
    s.emplace(l, r);
    AL[l].push_back(r);
  }
  for (int i = 0; i < v; i++) {
    if (dist[i] == -1) {
      dist[i] = 1;
      dfs(i);
    }
  }
  int ans = 0, idx;
  for (int i = 0; i < v; i++) {
    if (ans < dist[i]) {
      ans = dist[i];
      idx = i;
    }
  }
  cout << ans << '\n';
  cout << idx + 1 << ' ';
  get_output(idx);
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
