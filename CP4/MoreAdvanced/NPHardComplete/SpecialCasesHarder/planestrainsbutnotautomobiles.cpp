#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

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

  vi get_matches() {
    vi match(V - 2, -1);
    for (int i = 0; i < (V - 2) / 2; i++) {
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
};

int n, m;
set<int> airports;

void bfs(vector<vi> &AL, unordered_set<int> &start_nodes, bool left) {
  queue<int> q;
  vector<bool> visited(2 * n);
  for (int i : start_nodes) {
    q.push(i);
    visited[i] = true;
  }
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : AL[u]) {
      if (visited[v]) continue;
      visited[v] = true;
      q.push(v);
    }
  }
  int idx = left ? 0 : n;
  for (int i = idx; i < n + idx; i++) {
    if (visited[i]) airports.insert(i - idx);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  vector<vi> AL(2 * n);
  vector<pair<int, int>> EL;
  max_flow mf(2 * n + 2);
  int SOURCE = 2 * n, SINK = SOURCE + 1;
  for (int i = 0; i < n; i++) {
    mf.add_edge(SOURCE, i, 1);
    mf.add_edge(i + n, SINK, 1);
  }
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    AL[u].push_back(v + n);
    mf.add_edge(u, v + n, 1);
    EL.emplace_back(u, v + n);
  }
  int ans = n - mf.dinic(SOURCE, SINK) - 1;
  cout << ans << '\n';

  /*
   *  First let every unmatched edge go right and every matched edge go left.
   *  Then do a BFS/DFS from the set of unmatched vertices on the left.
   *  The vertices you will reach on the left are exactly the vertices that can be an end point of a path.
   *  Then let every unmatched edge go left and every matched edge go right.
   *  Then do a BFS/DFS from the set of unmatched vertices on the right.
   *  The vertices you will reach on the right are exactly the vertices that can be a start point of a path.
   *  The union of these sets is the set of vertices where you can visit the airport.
   */

  vi match = mf.get_matches();
  vector<vi> left_AL(2 * n), right_AL(2 * n);
  for (auto &[u, v] : EL) {
    if (match[u] == v && match[v] == u) {
      left_AL[v].push_back(u);
      right_AL[u].push_back(v);
    } else {
      left_AL[u].push_back(v);
      right_AL[v].push_back(u);
    }
  }
  unordered_set<int> unmatched_left, unmatched_right;
  for (int i = 0; i < n; i++) {
    if (match[i] == -1) unmatched_left.insert(i);
    if (match[i + n] == -1) unmatched_right.insert(i + n);
  }
  bfs(left_AL, unmatched_left, true);
  bfs(right_AL, unmatched_right, false);

  if (ans) {
    for (int i : airports) cout << i + 1 << ' ';
    cout << '\n';
  }
}
