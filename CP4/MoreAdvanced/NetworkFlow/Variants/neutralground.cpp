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
    int w, h, directions[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    cin >> w >> h;
    string arr[h];
    max_flow mf(2 * h * w + 2);
    int SOURCE = 2 * h * w, SINK = 2 * h * w + 1;
    for (int i = 0; i < h; i++) {
        cin >> arr[i];
        for (int j = 0; j < w; j++) {
            char c = arr[i][j];
            if (c == 'A') {
                mf.add_edge(SOURCE, i * w + j, 1e7);
                mf.add_edge(i * w + j, i * w + j + h * w, 1e7);
            } else if (c == 'B') {
                mf.add_edge(i * w + j, i * w + j + h * w, 1e7);
                mf.add_edge(i * w + j + h * w, SINK, 1e7);
            } else {
                mf.add_edge(i * w + j, i * w + j + h * w, arr[i][j] - '0');
            }
            for (auto& direction : directions) {
                int new_x = direction[0] + i;
                int new_y = direction[1] + j;
                if (new_x < 0 || new_x == h || new_y < 0 || new_y == w) continue;
                mf.add_edge(i * w + j + h * w, new_x * w + new_y, 1e7);
            }
        }
    }
    cout << mf.dinic(SOURCE, SINK);
}
