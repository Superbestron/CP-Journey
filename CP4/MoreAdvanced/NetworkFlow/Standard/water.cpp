#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;                             // large enough

class max_flow {
 public:
  int V;
  vector<edge> EL;
  vector<vi> AL;
  vi d, last;
  vector<ii> p;
  map<ii, int> edges;

  bool BFS(int s, int t) {                       // find augmenting path
    d.assign(V, -1);
    d[s] = 0;
    queue<int> q({s});
    p.assign(V, {-1, -1});                       // record BFS sp tree
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == t) break;                         // stop as sink t reached
      for (auto &idx : AL[u]) {                  // explore neighbors of u
        auto &[v, cap, flow] = EL[idx];          // stored in EL[idx]
        if ((cap - flow > 0) && (d[v] == -1))      // positive residual edge
          d[v] = d[u] + 1, q.push(v), p[v] = {u, idx}; // 3 lines in one!
      }
    }
    return d[t] != -1;                           // has an augmenting path
  }

  ll DFS(int u, int t, ll f = INF) {             // traverse from s->t
    if ((u == t) || (f == 0)) return f;
    for (int &i = last[u]; i < (int) AL[u].size(); ++i) { // from last edge
      auto &[v, cap, flow] = EL[AL[u][i]];
      if (d[v] != d[u] + 1) continue;              // not part of layer graph
      if (ll pushed = DFS(v, t, min(f, cap - flow))) {
        flow += pushed;
        auto &rflow = get<2>(EL[AL[u][i] ^ 1]);     // back edge
        rflow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

  max_flow(int initialV) : V(initialV) {
    EL.clear();
    AL.assign(V, vi());
  }

  // if you are adding a bidirectional edge u<->v with weight w into your
  // flow graph, set directed = false (default value is directed = true)
  void add_edge(int u, int v, ll w, bool directed = true) {
    if (u == v) return;                          // safeguard: no self loop
    EL.emplace_back(v, w, 0);                    // u->v, cap w, flow 0
    edges[{u, v}] = EL.size() - 1;
    AL[u].push_back(EL.size() - 1);                // remember this index
    EL.emplace_back(u, directed ? 0 : w, 0);     // back edge
    edges[{v, u}] = EL.size() - 1;
    AL[v].push_back(EL.size() - 1);                // remember this index
  }

  void update_edge(int u, int v, ll w) {
    if (u == v) return;
    if (!edges.count({u, v})) {
      add_edge(u, v, w, false);
      return;
    }
    int uv_edge_idx = edges[{u, v}];
    auto &[node1, cap1, flow1] = EL[uv_edge_idx];
    cap1 += w;
    int vu_edge_idx = edges[{v, u}];
    auto &[node2, cap2, flow2] = EL[vu_edge_idx];
    cap2 += w;
  }

  ll dinic(int s, int t) {
    ll mf = 0;                                   // mf stands for max_flow
    while (BFS(s, t)) {                          // an O(V^2*E) algorithm
      last.assign(V, 0);                         // important speedup
      while (ll f = DFS(s, t))                   // exhaust blocking flow
        mf += f;
    }
    return mf;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, p, k, a, b, c, cost = 0;
  cin >> n >> p >> k;
  max_flow mf(n);
  for (int i = 0; i < p; i++) {
    cin >> a >> b >> c;
    if (a == 1) a = 0;
    else if (a == 2) a = n - 1;
    else a -= 2;
    if (b == 1) b = 0;
    else if (b == 2) b = n - 1;
    else b -= 2;
    mf.add_edge(a, b, c, false);
  }
  cost += mf.dinic(0, n - 1);
  cout << cost << '\n';
  for (int i = 0; i < k; i++) {
    cin >> a >> b >> c;
    if (a == 1) a = 0;
    else if (a == 2) a = n - 1;
    else a -= 2;
    if (b == 1) b = 0;
    else if (b == 2) b = n - 1;
    else b -= 2;
    mf.update_edge(a, b, c);
    cost += mf.dinic(0, n - 1);
    cout << cost << '\n';
  }
}
