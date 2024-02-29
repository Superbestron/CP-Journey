#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

int t, n, u, v;
vector<vi> AL;

void solve() {
  cin >> n;
  AL.assign(n, {});
  for (int i = 0; i < n - 1; i++) {
    cin >> u >> v;
    u--; v--;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }
  if (n == 1) {
    cout << 0 << '\n';
    return;
  }
  queue<int> q;
  vi visited(n);
  visited[0] = true;
  q.push(0);
  int ans = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (AL[u].size() == 1) ans++;
    for (int v : AL[u]) {
      if (visited[v]) continue;
      visited[v] = true;
      q.push(v);
    }
  }
  cout << (ans + 1) / 2 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
