#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q, s, u, v, w, query;
    while (cin >> n >> m >> q >> s && !(n == 0 && m == 0 && q == 0 && s == 0)) {
        vector<vector<tuple<int, int>>> AL(n, vector<tuple<int, int>>());
        while (m--) {
            cin >> u >> v >> w;
            AL[u].emplace_back(v, w);
        }
        bool in_cycle[n];
        int cnt[n], dist[n];
        memset(cnt, 0, sizeof cnt);
        fill(dist, dist + n, 1e9);
        memset(in_cycle, false, sizeof in_cycle);
        dist[s] = 0;
        for (int i = 0; i < n - 1; i++) {
            bool modified = false;
            for (int u = 0; u < n; u++) {
                if (dist[u] == 1e9) continue;
                for (auto& [v, w] : AL[u]) {
                    if (dist[u] + w >= dist[v]) continue;
                    dist[v] = dist[u] + w;
                    modified = true;
                }
            }
            if (!modified) break;
        }

        for (int u = 0; u < n; u++) {
            if (dist[u] == 1e9) continue;
            for (auto& [v, w] : AL[u]) {
                if (dist[u] + w >= dist[v]) continue;
                in_cycle[v] = true;
            }
        }
        bool visited[n]; memset(visited, false, sizeof visited);
        for (int i = 0; i < n; i++) {
            if (!in_cycle[i] || visited[i]) continue;
            visited[i] = true;
            queue<int> t;
            t.push(i);
            while (!t.empty()) {
                int u = t.front(); t.pop();
                for (auto& p : AL[u]) {
                    int v = get<0>(p);
                    if (visited[v]) continue;
                    visited[v] = true;
                    t.push(v);
                }
            }
        }
        while (q--) {
            cin >> query;
            if (visited[query]) cout << "-Infinity\n";
            else if (dist[query] == 1e9) cout << "Impossible\n";
            else cout << dist[query] << '\n';
        }
        cout << '\n';
    }
}
