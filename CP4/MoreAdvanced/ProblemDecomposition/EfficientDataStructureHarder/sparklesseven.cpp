#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;                             // large enough
vector<string> strs = {"Twilight Sparkle", "Applejack", "Rarity", "Pinkie Pie", "Fluttershy", "Rainbow Dash", "Spike"};

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

  vector<vector<ii>> get_matches() {
    vector<vector<ii>> match(7);
    for (int i = 1; i <= 7; i++) {
      int cnt = 0;
      for (int idx : AL[i]) {
        auto &[v, cap, flow] = EL[idx];
        if (flow == 1) {
          match[cnt].emplace_back(i - 1, v - 7);
          cnt++;
        }
      }
    }
    return match;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int AM[7][7];
  for (auto &i : AM) {
    for (int &j : i) {
      cin >> j;
    }
  }
  int SOURCE = 0, SINK = 15;
  for (int i = 1; i <= 7; i++) {
    max_flow mf(16);
    for (int j = 0; j < 7; j++) {
      mf.add_edge(SOURCE, j + 1, i);
      for (int k = 0; k < 7; k++) {
        if (AM[j][k] == 0) continue;
        mf.add_edge(j + 1, 8 + k, 1);
      }
    }
    for (int k = 0; k < 7; k++) mf.add_edge(8 + k, SINK, 1);
    int ans = mf.dinic(SOURCE, SINK);
    if (ans == 7) {
      vector<vector<ii>> match = mf.get_matches();
      cout << i << '\n';
      for (int op = 0; op < i; op++) {
        auto &t = match[op];
        cout << t.size() << '\n';
        for (auto &[u, v] : t) {
          cout << strs[u] << ' ' << v << '\n';
        }
      }
      return 0;
    }
  }
  cout << "IMPOSSIBLE\n";
}
