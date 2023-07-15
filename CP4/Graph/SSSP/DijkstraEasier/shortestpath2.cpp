#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int, int> iiii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q, s, u, v, t0, p, d, query;
    while (cin >> n >> m >> q >> s && !(n == 0 && m == 0 && q == 0 && s == 0)) {
        vector<vector<iiii>> AL(n, vector<iiii>());
        vector<vector<tuple<int, int>>> parents(n, vector<tuple<int, int>>());
        while (m--) {
            cin >> u >> v >> t0 >> p >> d;
            AL[u].emplace_back(v, t0, p, d);
        }
        vector<int> dist(n, 1e9);
        dist[s] = 0;
        set<tuple<int, int>> pq;
        for (int u = 0; u < n; u++) pq.emplace(dist[u], u);

        while (!pq.empty()) {
            auto [t, u] = *pq.begin();
            pq.erase(pq.begin());
            for (auto& [v, t0, p, d] : AL[u]) {
                if (t > t0 && p == 0) continue;
                int w;
                if (t <= t0) w = d + t0 - t;
                else w = d + (p - (t - t0) % p) % p;
                if (t + w >= dist[v]) continue;
                pq.erase(pq.find({dist[v], v}));
                dist[v] = t + w;
                pq.emplace(dist[v], v);
            }
        }

        while (q--) {
            cin >> query;
            cout << (dist[query] == 1e9 ? "Impossible" : to_string(dist[query])) << '\n';
        }
        cout << '\n';
    }
}