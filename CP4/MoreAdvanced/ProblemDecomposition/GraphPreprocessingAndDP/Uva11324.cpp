#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int> ii;
typedef vector<int> vi;

enum { UNVISITED = 0, VISITED = 1 };

vector<vi> AL, AL_T, contracted_AL;
vi S, dfs_num, scc_index, scc_size;
int num_scc;

void kosaraju(int u, int pass) {
  dfs_num[u] = VISITED;
  vector<int>& neighbours = (pass == 1) ? AL[u] : AL_T[u];
  for (auto& v : neighbours) {
    if (dfs_num[v] == UNVISITED) kosaraju(v, pass);
  }
  if (pass == 1) S.push_back(u);
  else {
    scc_index[u] = num_scc;
    scc_size[num_scc]++;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, m;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    AL.assign(n, {});
    AL_T.assign(n, {});
    vector<ii> EL;
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      u--; v--;
      EL.emplace_back(u, v);
      AL[u].push_back(v);
      AL_T[v].push_back(u);
    }

    // Finding SCCs
    scc_index.assign(n, 0);
    scc_size.assign(n, 0);
    num_scc = 0;
    S.clear();
    dfs_num.assign(n, UNVISITED);
    for (int u = 0; u < n; u++) {
      if (dfs_num[u] == UNVISITED) kosaraju(u, 1);
    }
    dfs_num.assign(n, UNVISITED);
    for (int i = n - 1; i >= 0; i--) {
      if (dfs_num[S[i]] == UNVISITED) {
        kosaraju(S[i], 2);
        num_scc++;
      }
    }

    // Construct contracted AL
    set<ii> s;
    contracted_AL.assign(num_scc, {});
    vi in_deg(num_scc);
    for (auto &[u, v] : EL) {
      int node1 = min(scc_index[u], scc_index[v]);
      int node2 = max(scc_index[u], scc_index[v]);
      if (node1 == node2) continue;
      if (s.count({node1, node2})) continue;
      s.emplace(node1, node2);
      in_deg[node2]++;
      contracted_AL[node1].push_back(node2);
    }

    // Find longest path
    queue<int> q;
    vi dist(num_scc, 1e9);
    for (int i = 0; i < num_scc; i++) {
      if (in_deg[i] == 0) {
        q.push(i);
        dist[i] = -scc_size[i];
      }
    }
    int ans = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      ans = min(ans, dist[u]);
      for (int v : contracted_AL[u]) {
        if (dist[v] <= dist[u] - scc_size[v]) continue;
        dist[v] = dist[u] - scc_size[v];
        q.push(v);
      }
    }

    cout << -ans << '\n';
  }
}
