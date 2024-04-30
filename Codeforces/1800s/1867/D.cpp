#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;
vi a, dist, AL;

bool dfs(int u) {
  bool can = true;
  int dt = dist[u] + 1;
  int v = AL[u];
  if (dist[v] == -1e9) return true;
  if (dist[v] != -1) {
    if (dt - dist[v] != k) {
      return false;
    }
  } else {
    dist[v] = dt;
    can &= dfs(v);
    dist[v] = -1e9;
  }
  return can;
}

void solve() {
  cin >> n >> k;
  a.assign(n, 0);

  for (int &i : a) cin >> i;
  if (k == 1) {
    for (int i = 0; i < n; i++) {
      if (a[i] != i + 1) {
        cout << "NO\n";
        return;
      }
    }
    cout << "YES\n";
    return;
  }

  dist.assign(n, -1);
  AL.assign(n, -1);

  for (int i = 0; i < n; i++) {
    int val = a[i];
    AL[i] = val - 1;
  }

  bool can = true;
  for (int i = 0; i < n; i++) {
    if (dist[i] == -1) {
      dist[i] = 0;
      can &= dfs(i);
      dist[i] = -1e9;
    }
  }

  if (can) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}