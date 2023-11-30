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
  int s, r, f, t, n;
  string str;
  cin >> s >> r >> f >> t;
  int SOURCE = 0, SINK = s + 2 * t + 1, ctr = 1;
  max_flow mf(s + 2 * t + 2);
  unordered_map<string, int> m;
  unordered_set<int> raw, factory;
  for (int i = 0; i < r; i++) {
    cin >> str;
    if (!m.count(str)) {
      raw.insert(ctr);
      m[str] = ctr++;
    }
    mf.add_edge(SOURCE, m[str], 1);
  }
  for (int i = 0; i < f; i++) {
    cin >> str;
    if (!m.count(str)) {
      factory.insert(ctr);
      m[str] = ctr++;
    }
    mf.add_edge(m[str], SINK, 1);
  }
  for (int i = 1; i <= t; i++) {
    cin >> n;
    vector<int> raws, factories, dks;
    for (int j = 0; j < n; j++) {
      cin >> str;
      if (!m.count(str)) {
        m[str] = ctr++;
      }
      if (raw.count(m[str])) raws.push_back(m[str]);
      else if (factory.count(m[str])) factories.push_back(m[str]);
      else dks.push_back(m[str]);
    }
    for (int j : raws) mf.add_edge(j, s + i, 1);
    for (int j : factories) mf.add_edge(s + t + i, j, 1);
    for (int j : dks) {
      mf.add_edge(j, s + i, 1);
      mf.add_edge(s + t + i, j, 1);
    }
    mf.add_edge(s + i, s + t + i, 1);
  }
  cout << mf.dinic(SOURCE, SINK);
}
