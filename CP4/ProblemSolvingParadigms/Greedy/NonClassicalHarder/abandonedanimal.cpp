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
  // map<ii, int> edges;

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
    AL[u].push_back(EL.size() - 1);                // remember this index
    EL.emplace_back(u, directed ? 0 : w, 0);     // back edge
    AL[v].push_back(EL.size() - 1);                // remember this index
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

  // Only for 1 to 1 matching
//  vi get_matches() {
//    vi match(V - 2, -1);                         // Assumption is that indices 0 - (V - 3) refers to actual indices of
//    for (int i = 0; i < (V - 2) / 2; i++) {      // nodes while (V - 2) and (V - 1) refers to indices of source/sink
//      for (int idx : AL[i]) {
//        auto &[v, cap, flow] = EL[idx];
//        if (flow == 1) {
//          match[i] = v;
//          match[v] = i;
//          break;
//        }
//      }
//    }
//    return match;
//  }

//  void update_edge(int u, int v, ll w) {
//    if (u == v) return;
//    if (!edges.count({u, v})) {
//      add_edge(u, v, w, false);
//      return;
//    }
//    int uv_edge_idx = edges[{u, v}];
//    auto &[node1, cap1, flow1] = EL[uv_edge_idx];
//    cap1 += w;
//    int vu_edge_idx = edges[{v, u}];
//    auto &[node2, cap2, flow2] = EL[vu_edge_idx];
//    cap2 += w;
//  }

  vi find_min_cut(int s) {
    vi output;
    vi vis(V, -1);
    vis[s] = 0;
    queue<int> q({s});
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      output.push_back(u);
      for (auto &idx : AL[u]) {                  // explore neighbors of u
        auto &[v, cap, flow] = EL[idx];          // stored in EL[idx]
        if (vis[v] != -1) continue;
        if ((cap - flow > 0)) vis[v] = vis[u] + 1, q.push(v);
      }
    }
    return output;
  }

  void flow() {
    vi vis(V, -1);
    vis[0] = 0;
    queue<int> q({0});
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto &idx : AL[u]) {                  // explore neighbors of u
        auto &[v, cap, flow] = EL[idx];          // stored in EL[idx]
        if (vis[v] != -1) continue;
        vis[v] = vis[u] + 1;
        cout << u << ' ' << v << ' ' << flow << '\n';
        q.push(v);
      }
    }
  }

  bool check_unique() {
    vi vis(V, -1), dist(V, 0);
    vis[0] = 0;
    dist[0] = 1;
    queue<int> q({0});
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto &idx : AL[u]) {                  // explore neighbors of u
        auto &[v, cap, flow] = EL[idx];          // stored in EL[idx]
        if (u < v) dist[v] += dist[u];
        if (vis[v] != -1) continue;
        vis[v] = vis[u] + 1;
        q.push(v);
      }
    }
    return dist.back() == 1;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K, idx, M, ctr = 1;
  string s;
  cin >> N >> K;
  max_flow mf(K + 2);
  unordered_map<string, vi> mp;
  for (int i = 0; i < K; i++) {
    cin >> idx >> s;
    mp[s].push_back(idx);
  }
  cin >> M;
  vi prev(1, 0), temp(1, -1);
  vi &prev_stores = temp;
  for (int i = 0; i < M; i++) {
    cin >> s;
    vi next;
    for (int j : mp[s]) {
      for (int k = 0; k < prev.size(); k++) {
        if (prev_stores[k] > j) continue;
        mf.add_edge(prev[k], ctr, 1, true);
      }
      next.push_back(ctr++);
    }
    prev = next;
    prev_stores = mp[s];
  }
  for (int u : prev) {
    mf.add_edge(u, K + 1, 1, true);
  }
  int ans = mf.dinic(0, K + 1);
  if (ans == 0) cout << "impossible\n";
  else if (mf.check_unique()) cout << "unique\n";
  else cout << "ambiguous\n";
}
