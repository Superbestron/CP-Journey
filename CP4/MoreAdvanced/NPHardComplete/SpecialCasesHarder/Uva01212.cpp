#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18; // INF = 1e18, not 2^63-1 to avoid overflow

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
  int T, n1, n2;
  string s;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    if (i > 1) printf("\n");
    vector<pair<int, vector<int>>> telecom, mobile;
    vector<vector<int>> channels_used_by(300000);
    cin >> n1;
    cin.ignore();
    for (int j = 0; j < n1; j++) {
      getline(cin, s);
      istringstream str(s);
      int cost, channel;
      str >> cost;
      vector<int> channels;
      while (str >> channel) {
        channels.push_back(channel);
      }
      telecom.emplace_back(cost, std::move(channels));
    }
    cin >> n2;
    cin.ignore();
    for (int j = 0; j < n2; j++) {
      getline(cin, s);
      istringstream str(s);
      int cost, channel;
      str >> cost;
      vector<int> channels;
      while (str >> channel) {
        channels.push_back(channel);
      }
      mobile.emplace_back(cost, std::move(channels));
    }
    max_flow mf(1 + n1 + n2 + 1);
    int SOURCE = 0, SINK = 1 + n1 + n2, total_cost = 0;
    for (int j = 0; j < n1; j++) {
      auto &[cost, channels] = telecom[j];
      mf.add_edge(SOURCE, j + 1, cost);
      total_cost += cost;
      for (int channel : channels) {
        channels_used_by[channel - 1].push_back(j + 1);
      }
    }
    for (int j = 0; j < n2; j++) {
      auto &[cost, channels] = mobile[j];
      mf.add_edge(j + 1 + n1, SINK, cost);
      total_cost += cost;
      for (int channel : channels) {
        for (int conflict : channels_used_by[channel - 1]) {
          mf.add_edge(conflict, j + n1 + 1, 1e9);
        }
      }
    }
    ll cost = mf.dinic(SOURCE, SINK);
    printf("Case %d:\n%lld\n", i, total_cost - cost);
  }
}
