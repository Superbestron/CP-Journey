#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int> ii;

int N, E, V, e, F, ans;
vector<vector<int>> AL;
vector<bool> visited;

void dfs(int u) {
  V++;
  for (int v : AL[u]) {
    e++;
    if (visited[v]) F++;
    else {
      visited[v] = true;
      dfs(v);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  char n1, n2;
  while (cin >> N >> E) {
    unordered_map<char, int> m;
    AL.assign(N, {});
    for (int i = 0; i < E; i++) {
      cin >> n1 >> n2;
      if (!m.count(n1)) m[n1] = m.size();
      if (!m.count(n2)) m[n2] = m.size();
      int a = m[n1], b = m[n2];
      AL[a].push_back(b);
      AL[b].push_back(a);
    }
    stack<ii> s;
    visited.assign(N, false);
    ans = 0;
    for (int i = 0; i < N; i++) {
      if (visited[i]) continue;
      V = 0, e = 0, F = 0;
      visited[i] = true;
      dfs(i);
      ans += 1 + e / 2 - V;
    }
    cout << ans + 1 << '\n';
  }
}
