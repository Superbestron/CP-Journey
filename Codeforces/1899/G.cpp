#include <bits/stdc++.h>
using namespace std;

struct MergeSortTree {
  int n;
  vector<vector<int>> tree;

  void build(vector<int> &a, int x, int l, int r) {
    if (l + 1 == r) {
      tree[x] = {a[l]};
      return;
    }

    int m = (l + r) / 2;
    build(a, 2 * x + 1, l, m);
    build(a, 2 * x + 2, m, r);
    merge(tree[2 * x + 1].begin(), tree[2 * x + 1].end(),
          tree[2 * x + 2].begin(), tree[2 * x + 2].end(), back_inserter(tree[x]));
  }

  explicit MergeSortTree(vector<int> &a) : n(a.size()) {
    int SIZE = 1 << (31 - __builtin_clz(n) + bool(__builtin_popcount(n) - 1));
    tree.resize(2 * SIZE - 1);
    build(a, 0, 0, n);
  }

  int count(int lq, int rq, int mn, int mx, int x, int l, int r) {
    if (rq <= l || r <= lq) return 0;
    if (lq <= l && r <= rq) {
      return lower_bound(tree[x].begin(), tree[x].end(), mx)
          - lower_bound(tree[x].begin(), tree[x].end(), mn);
    }

    int m = (l + r) / 2;
    int a = count(lq, rq, mn, mx, 2 * x + 1, l, m);
    int b = count(lq, rq, mn, mx, 2 * x + 2, m, r);
    return a + b;
  }

  // [lq, rq)
  // From lq (inclusive) to rq (exclusive), count how many numbers are within [mn, mx]
  int count(int lq, int rq, int mn, int mx) {
    return count(lq, rq, mn, mx, 0, 0, n);
  }
};

int t, n, q, c, d, ctr, l, r, x;
vector<vector<int>> AL;
vector<bool> visited;
vector<int> entry, ext;

void dfs(int u) {
  entry[u] = ctr++;
  for (int v : AL[u]) {
    if (visited[v]) continue;
    visited[v] = true;
    dfs(v);
  }
  ext[u] = ctr;
}

inline void solve() {
  cin >> n >> q;
  ctr = 0;
  AL.assign(n, {});
  visited.assign(n, false);
  entry.assign(n, 0);
  ext.assign(n, 0);
  unordered_map<int, int> m;
  vector<int> p(n), a(n);
  for (int i = 0; i < n - 1; i++) {
    cin >> c >> d;
    c--; d--;
    AL[c].push_back(d);
    AL[d].push_back(c);
  }
  for (int &i : p) {
    cin >> i;
    i--;
  }
  visited[0] = true;
  dfs(0);
  for (int i = 0; i < n; i++) a[i] = entry[p[i]];
  MergeSortTree tree(a);

  for (int i = 0; i < q; i++) {
    cin >> l >> r >> x;
    l--; r--; x--;
    if (tree.count(l, r + 1, entry[x], ext[x])) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
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
