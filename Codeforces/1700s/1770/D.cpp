#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

int t, n;
const int MOD = 998244353;

ll mod(ll a, int m) {                            // returns a (mod m)
  return ((a % m) + m) % m;                        // ensure positive answer
}

ll modPow(ll b, int p, int m) {                  // assume 0 <= b < m
  if (p == 0) return 1;
  ll ans = modPow(b, p / 2, m);                    // this is O(log p)
  ans = mod(ans * ans, m);                         // double it first
  if (p & 1) ans = mod(ans * b, m);                  // *b if p is odd
  return ans;                                    // ans always in [0..m-1]
}

void solve() {
  cin >> n;
  vi a(n), b(n);
  for (int &i : a) cin >> i, i--;
  for (int &i : b) cin >> i, i--;
  vector<vi> AL(n);
  vi dist(n, 1e9);
  for (int i = 0; i < n; i++) {
    AL[a[i]].push_back(b[i]);
    AL[b[i]].push_back(a[i]);
  }
  bool can = true;
  ll ans = 1;
  for (int i = 0; i < n; i++) {
    if (dist[i] != 1e9) continue;
    bool loop = false;
    int edges = 0, sz = 0;
    sz++;
    dist[i] = 0;
    queue<int> q;
    q.push(i);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : AL[u]) {
        edges++;
        if (u == v) loop = true;
        if (dist[v] != 1e9) continue;
        dist[v] = dist[u] + 1;
        sz++;
        q.push(v);
      }
    }
    edges >>= 1;
    if (edges != sz) {
      can = false; break;
    }
    if (loop) {
      ans = (ans * n) % MOD;
    } else {
      ans = (ans * 2) % MOD;
    }
  }
  if (!can) cout << 0 << '\n';
  else {
    cout << ans << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
