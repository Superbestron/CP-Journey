#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

class UnionFind {                                // OOP style
 private:
  vi p, rank;                           // vi p is the key part
 public:
  explicit UnionFind(int N) {
    p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
    rank.assign(N, 0);                           // optional speedup
  }

  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items
    if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
    p[x] = y;                                    // set x under y
    if (rank[x] == rank[y]) ++rank[y];           // optional speedup
  }
};

void solve() {
  int n, m, q, l, r;
  cin >> n >> m;
  UnionFind ufds(n);
  vector<vi> AL(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    AL[u].push_back(v);
    AL[v].push_back(u);
    ufds.unionSet(u, v);
  }
  cin >> q;
  for (int i = 0; i < q; i++) {
    cin >> l >> r;
    if (!ufds.isSameSet(l, r)) {
      cout << -1 << '\n';
      continue;
    }
    queue<int> que;
    vi dist(n, -1), src(n);
    dist[l] = 0, dist[r] = 0;
    src[r] = 1;
    que.push(l);
    que.push(r);
    while (!que.empty()) {
      int u = que.front(); que.pop();
      for (int v : AL[u]) {
        if (dist[v] != -1 && src[u] != src[v]) {
          cout << dist[u] + dist[v] + 1 << '\n';
          goto done;
        }
        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          src[v] = src[u];
          que.push(v);
        }
      }
    }
    done:
    continue;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
