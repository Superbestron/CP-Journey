#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

int R, S, L, A, B;
int SOURCE = 0, SINK;
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

  ll DFS(int u, int t, ll f = INF) {             // traverse from s.t
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

  // if you are adding a bidirectional edge u<.v with weight w into your
  // flow graph, set directed = false (default value is directed = true)
  void add_edge(int u, int v, ll w, bool directed = true) {
    if (u == v) return;                          // safeguard: no self loop
    EL.emplace_back(v, w, 0);                    // u.v, cap w, flow 0
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

  void print() {
    for (int i = 1; i <= L; i++) {
      int idx = AL[i][1], idx2 = AL[i][2];
      auto &temp1 = EL[idx];
      auto &temp2 = EL[idx2];
      if (get<2>(temp1) == 1) {
        cout << "INDV " << get<0>(temp1) - L << '\n';
      } else {
        cout << "CORP " << get<0>(temp2) - L - R << '\n';
      }
    }
  }
};

max_flow curr_mf(0);

bool can(int cap) {
  max_flow curr = curr_mf;
  for (int i = L + 1; i <= L + R + S; i++) {
    curr.add_edge(i, SINK, cap);
  }
  int ans = curr.dinic(SOURCE, SINK);
  return ans == L;
}

// [1, L] -> lawsuits, [L + 1, L + R] -> individuals, [L + R + 1, L + R + S] -> corporations

int main() {
  cin >> R >> S >> L;
  SINK = L + R + S + 1;
  curr_mf = max_flow(L + R + S + 2);
  for (int i = 1; i <= L; i++) {
    cin >> A >> B;
    curr_mf.add_edge(SOURCE, i, 1);
    curr_mf.add_edge(i, A + L, 1);
    curr_mf.add_edge(i, B + L + R, 1);
  }
  int lo = 1, hi = 1e9;
  while (hi > lo) {
    int mid = lo + (hi - lo) / 2;
    can(mid) ? hi = mid : lo = mid + 1;
  }
  for (int i = L + 1; i <= L + R + S; i++) {
    curr_mf.add_edge(i, SINK, lo);
  }
  curr_mf.dinic(SOURCE, SINK);
  curr_mf.print();
}
