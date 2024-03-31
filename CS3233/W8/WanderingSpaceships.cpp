#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef long double ld;

const ll INF = 1e18;                             // large enough

class max_flow {
 private:
  int V;
  vector<edge> EL, output;
  vector<vi> AL;
  vi d, last;
  vector<ii> p;

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
    return mf;
  }
};

ll t, actual_n, n, m, k, l, xf, yf, xt, yt;

void solve() {
	cin >> actual_n >> m >> k >> l >> xf >> yf >> xt >> yt;
	n = min(actual_n, m);
	viii stars;
	for (int i = 0; i < k; i++) {
		int xa, ya, a;
		cin >> xa >> ya >> a;
		stars.emplace_back(xa, ya, a);
	}

	int SOURCE = 0, AFTERSOURCE = 1, SINK = 2 + 2 * k;
	max_flow mf(2 + 2 * k + 1);
	mf.add_edge(SOURCE, AFTERSOURCE, n, true);
	for (int i = 0; i < k; i++) {
		auto &[xa, ya, a] = stars[i];
		ld dist = hypotf(abs(xa - xf), abs(ya - yf));
		if (dist > l) continue;
		mf.add_edge(AFTERSOURCE, i + 2, 1e9, true);
	}

	// edges btw diff stars
	for (int i = 0; i < k; i++) {
		auto &[xa1, ya1, a1] = stars[i];
		for (int j = i + 1; j < k; j++) {
			auto &[xa2, ya2, a2] = stars[j];
			ld dist = hypotf(abs(xa1 - xa2), abs(ya1 - ya2));
			if (dist > l) continue;
			mf.add_edge(i + 2 + k, j + 2, 1e9, true);
			mf.add_edge(j + 2 + k, i + 2, 1e9, true);
		}
	}

	// vertex capacity of star, and join to last star
	for (int i = 0; i < k; i++) {
		auto &[xa, ya, a] = stars[i];
		mf.add_edge(i + 2, i + 2 + k, a, true);

		ld dist = hypotf(abs(xt - xa), abs(yt - ya));
		if (dist > l) continue;
		mf.add_edge(i + 2 + k, SINK, 1e9, true);
	}

	ld dist_src_to_tar = hypotf(abs(xf - xt), abs(yf - yt));
	if (dist_src_to_tar <= l) {
		mf.add_edge(AFTERSOURCE, SINK, 1e9, true);
	}
	ll ans = mf.dinic(SOURCE, SINK);
	cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
	solve();
  }
}
