#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> AL;
vector<int> children_sizes;
priority_queue<int, vector<int>, greater<>> pq;

int dfs(int u, int p, bool first) {
  int ans = 1;
  for (int v : AL[u]) {
    if (v == p) continue;
    int sz = dfs(v, u, false);
    ans += sz;
    if (first) {
      children_sizes.push_back(sz);
      pq.push(sz);
      if (pq.size() > 2) pq.pop();
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, a, b, best_n1 = 0, best_n2 = INT32_MAX;
  cin >> n;
  n++;
  AL.assign(n, {});
  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b;
    AL[a].push_back(b);
    AL[b].push_back(a);
  }
  // try all junction
  for (int i = 0; i < n; i++) {
    if (AL[i].size() == 1) continue;
    children_sizes.clear();
    dfs(i, -1, true);
    int n1 = 0;
    int sum = children_sizes[0];
    for (int j = 1; j < children_sizes.size(); j++) {
      n1 += sum * children_sizes[j];
      sum += children_sizes[j];
    }
    if (n1 > best_n1) {
      best_n1 = n1;
      if (pq.size() == 2) {
        int t1 = pq.top(); pq.pop();
        best_n2 = n1 - t1 * pq.top();
      } else best_n2 = best_n1;
    }
    while (!pq.empty()) pq.pop();
  }
  cout << best_n1 << ' ' << best_n2 << '\n';
}