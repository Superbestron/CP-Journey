#include <bits/stdc++.h>
#include "SparseTable.cpp"
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int idx = 0;
vi L, E, H, sz;
vector<vi> AL;

int dfs(int cur, int depth) {
  H[cur] = idx;
  E[idx] = cur;
  L[idx++] = depth;
  int sum = 1;
  for (auto &nxt : AL[cur]) {
    sum += dfs(nxt, depth + 1);
    E[idx] = cur;                              // backtrack to current node
    L[idx++] = depth;
  }
  sz[cur] = sum;
  return sum;
}

void buildRMQ() {
  sz[0] = 1;
  dfs(0, 0);                       // we assume that the root is at index 0
}

void solve() {
  int n, m, u, v, q, l, r;
  cin >> n >> m;
  L.assign(2 * n, 0);
  E.assign(2 * n, 0);
  H.assign(n, 0);
  sz.assign(n, 0);
  AL.assign(n, {});
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }
  buildRMQ();
  SparseTable SpT(L);
  cin >> q;
  for (int i = 0; i < q; i++) {
    cin >> l >> r;
    int lca = E[SpT.RMQ(min(H[l], H[r]), max(H[l], H[r]))];
    int height_l = L[H[l]], height_r = L[H[r]];
    cout << height_l + height_r - 2 * lca << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
