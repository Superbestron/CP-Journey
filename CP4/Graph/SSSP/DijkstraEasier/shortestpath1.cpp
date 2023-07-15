#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q, s, a, b, w, dest;
    while (cin >> n >> m >> q >> s && !(n == 0 && m == 0 && q == 0 && s == 0)) {
        vector<vector<tuple<int, int>>> AL(n, vector<tuple<int, int>>());
        while (m--) {
            cin >> a >> b >> w;
            AL[a].emplace_back(b, w);
        }
        vector<int> dist(n, 1e9);
        dist[s] = 0;
        set<tuple<int, int>> pq;
        for (int u = 0; u < n; u++) pq.emplace(dist[u], u);

        while (!pq.empty()) {
            auto [d, u] = *pq.begin();
            pq.erase(pq.begin());
            for (auto& [v, w] : AL[u]) {
                if (dist[u] + w >= dist[v]) continue;
                pq.erase(pq.find({dist[v], v}));
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }

        while (q--) {
            cin >> dest;
            cout << (dist[dest] == 1e9 ? "Impossible" : to_string(dist[dest])) << '\n';
        }
        cout << '\n';
    }
}