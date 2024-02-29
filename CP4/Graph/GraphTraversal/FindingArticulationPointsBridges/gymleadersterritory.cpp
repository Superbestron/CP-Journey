#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

int n, k, m;

void solve() {
  cin >> n >> k >> m;
  k--;
  queue<int> q;
  vector<unordered_set<int>> AL(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    AL[u].insert(v);
    AL[v].insert(u);
  }
  for (int i = 0; i < n; i++) {
    if (AL[i].size() == 1) q.push(i);
  }
  bool found = AL[k].size() <= 1;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (AL[u].size() != 1) continue;
    if (u == k) found = true;
    int v = *AL[u].begin();
    AL[u].erase(v);
    AL[v].erase(u);
    if (AL[v].size() <= 1 && v == k) found = true;
    if (AL[v].size() == 1) q.push(v);

  }
  if (found) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
