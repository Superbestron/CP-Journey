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

  bool BFS(int s, int t) {                       // find augmenting path
    d.assign(V, -1); d[s] = 0;
    queue<int> q({s});
    p.assign(V, {-1, -1});                       // record BFS sp tree
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == t) break;                         // stop as sink t reached
      for (auto &idx : AL[u]) {                  // explore neighbors of u
        auto &[v, cap, flow] = EL[idx];          // stored in EL[idx]
        if ((cap-flow > 0) && (d[v] == -1))      // positive residual edge
          d[v] = d[u]+1, q.push(v), p[v] = {u, idx}; // 3 lines in one!
      }
    }
    return d[t] != -1;                           // has an augmenting path
  }

  ll DFS(int u, int t, ll f = INF) {             // traverse from s->t
    if ((u == t) || (f == 0)) return f;
    for (int &i = last[u]; i < (int)AL[u].size(); ++i) { // from last edge
      auto &[v, cap, flow] = EL[AL[u][i]];
      if (d[v] != d[u]+1) continue;              // not part of layer graph
      if (ll pushed = DFS(v, t, min(f, cap-flow))) {
        flow += pushed;
        auto &rflow = get<2>(EL[AL[u][i]^1]);     // back edge
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
    AL[u].push_back(EL.size()-1);                // remember this index
    EL.emplace_back(u, directed ? 0 : w, 0);     // back edge
    AL[v].push_back(EL.size()-1);                // remember this index
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
  int n, q, s, queue;
  cin >> n >> q >> s;
  vector<int> s_to_q(s), q_sz(q), window(n);
  int SOURCE = 0, graph_size = s + 2 * q + 1, SINK = n * graph_size + 1;
  max_flow mf(n * graph_size + 2);
  for (int i = 1; i <= s; i++) {
    cin >> queue;
    for (int j = 0; j < n; j++) {
      // s -> qin
      mf.add_edge(i + j * graph_size, s + queue + j * graph_size, 1e9);
    }
  }
  for (int i = 1; i <= q; i++) {
    cin >> q_sz[i - 1];
    for (int j = 0; j < n; j++) {
      // qin -> qout
      mf.add_edge(s + i + j * graph_size, s + q + i + j * graph_size, q_sz[i - 1]);
      // qout -> datain
      mf.add_edge(s + q + i + j * graph_size, s + 2 * q + j * graph_size, 1e9);
      // qout ->  next qin
      if (j != n - 1) mf.add_edge(s + q + i + j * graph_size, s + i + (j + 1) * graph_size, q_sz[i - 1]);
    }
  }
  ll total_data = 0;
  for (int i = 0; i < n; i++) {
    cin >> window[i];
    mf.add_edge(s + 2 * q + i * graph_size, SINK, window[i]);
    for (int j = 1; j <= s; j++) {
      cin >> queue;
      total_data += queue;
      mf.add_edge(SOURCE, j + i * graph_size, queue);
    }
  }

  ll ans = mf.dinic(SOURCE, SINK);
  if (ans == total_data) cout << "possible";
  else cout << "impossible";
}
