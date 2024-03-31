#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

int t, r, c;
const ll INF = 1e18;                             // large enough

class max_flow {
 private:
  int V;
  vector<edge> EL, output;
  vector<vi> AL;
  vi d, last;
  vector<ii> p;
  map<ii, int> edges;

  void gen_output() {
    set<ii> st;
    for (int u = 0; u < V; u++) {
      for (int idx : AL[u]) {
        auto &[v, cap, flow] = EL[idx];
        if (st.count({min(u, v), max(u, v)})) continue;
        st.emplace(min(u, v), max(u, v));
        output.emplace_back(u, v, abs(flow));
      }
    }
  }

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

 public:
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
    gen_output();
    return mf;
  }

  // Only for 1 to 1 matching
  vi get_matches() {
    vi match(V - 2, -1);                         // Assumption is that indices 0 - (V - 3) refers to actual indices of
    for (int i = 0; i < (V - 2) / 2; i++) {      // nodes while (V - 2) and (V - 1) refers to indices of source/sink
      for (int idx : AL[i]) {
        auto &[v, cap, flow] = EL[idx];
        if (flow == 1) {
          match[i] = v;
          match[v] = i;
          break;
        }
      }
    }
    return match;
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

  vi find_min_cut(int s) {
    vi ans;
    vi vis(V, -1);
    vis[s] = 0;
    queue<int> q({s});
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      ans.push_back(u);
      for (auto &idx : AL[u]) {                  // explore neighbors of u
        auto &[v, cap, flow] = EL[idx];          // stored in EL[idx]
        if (vis[v] != -1) continue;
        if ((cap - flow > 0)) vis[v] = vis[u] + 1, q.push(v);
      }
    }
    return ans;
  }

  vector<edge> get_output() {
    return output;
  }
};

int direc[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void solve() {
  cin >> r >> c;
  vector<string> b(r);
  vector<vi> a(r, vi(c));
  max_flow mf(r * c + 2);
  int SOURCE = r * c, SINK = SOURCE + 1;
  int sum = 0;
  for (int i = 0; i < r; i++) {
    cin >> b[i];
    for (int j = 0; j < c; j++) {
      a[i][j] = b[i][j] - '0';
      sum += a[i][j];
      int node_no = i * c + j;
    }
  }
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      int node_no = i * c + j;
      if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) {
        mf.add_edge(node_no, SINK, a[i][j], true);
        continue;
      } else {
        mf.add_edge(SOURCE, node_no, a[i][j], true);
      }
      for (auto &d : direc) {
        int new_x = i + d[0];
        int new_y = j + d[1];
        if (new_x < 0 || new_x >= r || new_y < 0 || new_y >= c) continue;
        int next_node_no = new_x * c + new_y;
        mf.add_edge(node_no, next_node_no, 1e9, true);
      }
    }
  }
  cout << sum - mf.dinic(SOURCE, SINK) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
