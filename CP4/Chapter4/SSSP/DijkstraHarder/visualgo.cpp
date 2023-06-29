#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int V, E, u, v, w, s, t;
    cin >> V >> E;
    priority_queue<ii, vector<ii>, greater<>> pq;
    vector<int> dist(V, 1e9), ways(V, 0);
    vector<vector<ii>> AL(V, vector<ii>());
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        AL[u].emplace_back(v, w);
    }
    cin >> s >> t;
    ways[s] = 1;
    dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : AL[u]) {
            if (d + w > dist[v]) continue;
            if (d + w == dist[v]) {
                ways[v] += ways[u];
                continue;
            }
            ways[v] = ways[u];
            dist[v] = d + w;
            pq.emplace(dist[v], v);
        }
    }

    cout << ways[t];
}