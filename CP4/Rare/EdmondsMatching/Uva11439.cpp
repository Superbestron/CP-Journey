#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;

class Blossom {
 private:
  int n, timer, matchings;
  vi mate, label, parent, orig, aux, q;
  vector<vi> graph;

  int lca(int x, int y) {
    for (timer++;; swap(x, y)) {
      if (x == -1) continue;
      if (aux[x] == timer) return x;
      aux[x] = timer;
      x = (mate[x] == -1 ? -1 : orig[parent[mate[x]]]);
    }
  }

  void blossom(int v, int w, int a) {
    while (orig[v] != a) {
      parent[v] = w;
      w = mate[v];
      if (label[w] == 1) label[w] = 0, q.push_back(w);
      orig[v] = orig[w] = a;
      v = parent[w];
    }
  }

  void augment(int v) {
    while (v != -1) {
      int pv = parent[v], nv = mate[pv];
      mate[v] = pv;
      mate[pv] = v;
      v = nv;
    }
  };

  int bfs(int root) {
    fill(label.begin(), label.end(), -1);
    iota(orig.begin(), orig.end(), 0);
    q.clear();
    label[root] = 0;
    q.push_back(root);
    for (int i = 0; i < (int) q.size(); ++i) {
      int v = q[i];
      for (auto x : graph[v]) {
        if (label[x] == -1) {
          label[x] = 1;
          parent[x] = v;
          if (mate[x] == -1)
            return augment(x), 1;
          label[mate[x]] = 0;
          q.push_back(mate[x]);
        } else if (label[x] == 0 && orig[v] != orig[x]) {
          int a = lca(orig[v], orig[x]);
          blossom(x, v, a);
          blossom(v, x, a);
        }
      }
    }
    return 0;
  };

 public:
  Blossom(vector<vi> &AL) : graph(AL), n(AL.size()), timer(-1) {
    mate.assign(n, -1);
    label.assign(n, 0);
    parent.assign(n, 0);
    orig.assign(n, 0);
    aux.assign(n, -1);
  }

  pair<int, vi> blossom_matching() {
    matchings = 0;
    for (int i = 0; i < n; i++)
      if (mate[i] == -1) {
        matchings += bfs(i);
      }
    return {matchings, mate};
  }
};

int T, N, V, val;
vvi AL;

bool can(int x) {
  vvi AL2(V);
  for (int i = 0; i < V; i++) {
    for (int j = i + 1; j < V; j++) {
      if (AL[i][j] >= x) {
        AL2[i].push_back(j);
        AL2[j].push_back(i);
      }
    }
  }
  Blossom eb(AL2);
  auto [ans, mate] = eb.blossom_matching();
  return ans * 2 == V;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cin >> N;
    V = 1 << N;
    AL.assign(V, vi(V));
    for (int i = 0; i < V; i++) {
      for (int j = i + 1; j < V; j++) {
        cin >> val;
        AL[j][i] = AL[i][j] = val;
      }
    }
    int lo = 0, hi = 2e9;
    while (hi > lo) {
      int mid = lo + (hi - lo + 1) / 2;
      can(mid) ? lo = mid : hi = mid - 1;
    }
    cout << "Case " << tc << ": " << lo << '\n';
  }
}
