#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;                             // large enough

unordered_map<int, int> actual_to_withoutN_idx;
int num_matches_without_N;
vector<int> score;
vector<tuple<int, int, int>> matches_without_N;

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

  void update() {
    for (int i = 1; i <= num_matches_without_N; i++) {
      for (int ne : AL[i]) {
        int idx = get<0>(EL[ne]);
        if (idx == 0) continue;
        int actual_idx = actual_to_withoutN_idx[i - 1];
        int temp = get<2>(EL[ne]);
        if (temp == 2 && idx - num_matches_without_N == get<1>(matches_without_N[i - 1])) {
          score[actual_idx] = temp;
        } else if (temp == 1) {
          score[actual_idx] = temp;
        }
      }
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M, a, b;
  while (cin >> N && N != -1) {
    cin >> M;
    vector<int> points(N);
    actual_to_withoutN_idx.clear();
    matches_without_N.clear();
    score.assign(M, 0);
    for (int &i : points) cin >> i;
    for (int i = 0; i < M; i++) {
      cin >> a >> b;
      if (a == N) {
        points[N - 1] += 2;
      } else if (b == N) {
        score[i] = 2;
        points[N - 1] += 2;
      } else {
        matches_without_N.emplace_back(a, b, i);
      }
    }
    num_matches_without_N = matches_without_N.size();
    int SOURCE = 0, SINK = num_matches_without_N + N;
    max_flow mf(1 + SINK);
    for (int i = 1; i <= num_matches_without_N; i++) {
      auto &[n1, n2, idx] = matches_without_N[i - 1];
      actual_to_withoutN_idx[i - 1] = idx;
      mf.add_edge(SOURCE, i, 2);
      mf.add_edge(i, num_matches_without_N + n1, 2);
      mf.add_edge(i, num_matches_without_N + n2, 2);
    }
    bool ok = true;
    for (int i = 1; i < N; i++) {
      if (points[N - 1] - points[i - 1] - 1 < 0) {
        ok = false; break;
      } else mf.add_edge(num_matches_without_N + i, SINK, points[N - 1] - points[i - 1] - 1);
    }
    if (!ok) cout << "NO\n";
    else {
      int flow = mf.dinic(SOURCE, SINK);
      mf.update();
      if (flow < 2 * num_matches_without_N) cout << "NO\n";
      else {
        for (int i = 0; i < M; i++) {
          cout << score[i] << ' ';
        }
        cout << '\n';
      }
    }
  }
}
