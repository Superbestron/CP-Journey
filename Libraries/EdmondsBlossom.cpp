#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

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
  Blossom(vector<vi> &AL) : n(AL.size()), timer(-1), graph(AL) {
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

int main() {
  int N, M, u, v;
  cin >> N >> M;
  vector<vi> AL(N);
  for (int i = 0; i < M; i++) {
    cin >> u >> v;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }
  Blossom eb(AL);
  auto [cnt, match] = eb.blossom_matching();
  cout << cnt << '\n';
  for (int i = 0; i < N; i++)
    if (i < match[i]) cout << i << " " << match[i] << endl;
}
