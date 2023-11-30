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

  void print() {
    for (int i = 26; i < 36; i++) {
      bool found = false;
      for (int idx : AL[i]) {
        int pushed = get<2>(EL[idx]);
        if (get<0>(EL[idx]) >= 36) continue;
        if (pushed == -1) {
          found = true;
          cout << static_cast<char>('A' + get<0>(EL[idx]));
          break;
        }
      }
      if (!found) cout << '_';
    }
    cout << '\n';
  }
};

vector<string> split(string& s, char delimiter) {
  size_t pos;
  string token;
  vector<string> arr;
  if (s.empty()) return arr;
  while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    arr.emplace_back(token);
    s.erase(0, pos + 1);
  }
  arr.emplace_back(s);
  return arr;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  max_flow mf(38);
  int SOURCE = 36, SINK = 37, n = 0;
  while (getline(cin, s)) {
    if (s.empty()) {
      for (int i = 26; i < 36; i++) {
        mf.add_edge(i, SINK, 1);
      }
      int max_f = mf.dinic(SOURCE, SINK);
      if (max_f < n) cout << "!\n";
      else mf.print();
      mf = max_flow(38);
      n = 0;
    } else {
      vector<string> v = split(s, ' ');
      v[1].pop_back();
      for (char c : v[1]) {
        mf.add_edge(v[0][0] - 'A', c - '0' + 26, 1);
      }
      int num = v[0][1] - '0';
      n += num;
      mf.add_edge(SOURCE, v[0][0] - 'A', num);
    }
  }
  for (int i = 26; i < 36; i++) {
    mf.add_edge(i, SINK, 1);
  }
  int max_f = mf.dinic(SOURCE, SINK);
  if (max_f < n) cout << "!\n";
  else mf.print();
}