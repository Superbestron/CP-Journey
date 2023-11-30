#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll, ll> edge;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll INF = 1e18; // INF = 1e18, not 2^63-1 to avoid overflow

class min_cost_max_flow {
 private:
  int V;
  ll total_cost;
  vector<edge> EL;
  vector<vi> AL;
  vll d;
  vi last, vis;

  bool SPFA(int s, int cost) { // SPFA to find augmenting path in residual graph
    d.assign(V, INF); d[s] = 0; vis[s] = 1;
    queue<int> q({s});
    while (!q.empty()) {
      int u = q.front(); q.pop(); vis[u] = 0;
      for (auto &idx : AL[u]) {                  // explore neighbors of u
        auto &[v, cap, flow, cost] = EL[idx];          // stored in EL[idx]
        if ((cap-flow > 0) && (d[v] > d[u] + cost)) {      // positive residual edge
          d[v] = d[u]+cost;
          if(!vis[v]) q.push(v), vis[v] = 1;
        }
      }
    }
    return d[cost] != INF;                           // has an augmenting path
  }

  ll DFS(int u, int t, ll f = INF) {             // traverse from s->t
    if ((u == t) || (f == 0)) return f;
    vis[u] = 1;
    for (int &i = last[u]; i < (int)AL[u].size(); ++i) { // from last edge
      auto &[v, cap, flow, cost] = EL[AL[u][i]];
      if (!vis[v] && d[v] == d[u]+cost) {                      // in current layer graph
        if (ll pushed = DFS(v, t, min(f, cap-flow))) {
          total_cost += pushed * cost;
          flow += pushed;
          auto &[rv, rcap, rflow, rcost] = EL[AL[u][i]^1]; // back edge
          rflow -= pushed;
          vis[u] = 0;
          return pushed;
        }
      }
    }
    vis[u] = 0;
    return 0;
  }

 public:
  min_cost_max_flow(int initialV) : V(initialV), total_cost(0) {
    EL.clear();
    AL.assign(V, vi());
    vis.assign(V, 0);
  }

  // if you are adding a bidirectional edge u<->v with weight w into your
  // flow graph, set directed = false (default value is directed = true)
  void add_edge(int u, int v, ll w, ll c, bool directed = true) {
    if (u == v) return;                          // safeguard: no self loop
    EL.emplace_back(v, w, 0, c);                 // u->v, cap w, flow 0, cost c
    AL[u].push_back(EL.size()-1);                // remember this index
    EL.emplace_back(u, 0, 0, -c);                // back edge
    AL[v].push_back(EL.size()-1);                // remember this index
    if (!directed) add_edge(v, u, w, c);         // add again in reverse
  }

  pair<ll, ll> mcmf(int s, int t) {  // cap the flow at tf
    ll mf = 0;                                  // mf stands for max_flow
    while (SPFA(s, t)) {            // at most run min(tf, V) times
      last.assign(V, 0);                      // important speedup
      while (ll f = DFS(s, t))       // exhaust blocking flows in O(E)
        mf += f;                            // send at most tf-mf more flow
    }
    return {mf, total_cost};  // note to check if mf == tf if needed
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int P, R, L, a, b;
  cin >> P >> R >> L;
  min_cost_max_flow mf(R + 3);
  int SOURCE = R, SINK = R + 1, SUPERSOURCE = R + 2;
  for (int i = 0; i < L; i++) {
    cin >> a >> b;
    if (a < 0) a += R + 2;
    if (b < 0) b += R + 2;
    mf.add_edge(a, b, 1, 1, false);
  }
  mf.add_edge(SUPERSOURCE, SOURCE, P, 0);
  auto [max_flow, total_cost] = mf.mcmf(SUPERSOURCE, SINK);
  if (max_flow < P) cout << P - max_flow << " people left behind\n";
  else cout << total_cost << '\n';
}
