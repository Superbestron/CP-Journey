#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int P, T, a, b, w, cost = 0;
    cin >> P >> T;
    vector<vector<tuple<int, int>>> AL(P, vector<tuple<int, int>>());
    vector<vector<tuple<int, int>>> parents(P, vector<tuple<int, int>>());
    while (T--) {
        cin >> a >> b >> w;
        AL[a].emplace_back(b, w);
        AL[b].emplace_back(a, w);
    }
    vector<int> dist(P, 1e9);
    dist[0] = 0;
    set<tuple<int, int>> pq;
    for (int u = 0; u < P; u++) pq.emplace(dist[u], u);

    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        for (auto& [v, w] : AL[u]) {
            if (dist[u] + w > dist[v]) continue;
            if (dist[u] + w == dist[v]) {
                parents[v].emplace_back(u, w);
                continue;
            }
            parents[v].clear();
            pq.erase(pq.find({dist[v], v}));
            dist[v] = dist[u] + w;
            parents[v].emplace_back(u, w);
            pq.emplace(dist[v], v);
        }
    }

    queue<int> q;
    q.push(P - 1);
    dist.assign(P, 1e9);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& [v, w] : parents[u]) {
            cost += w;
            if (dist[v] != 1e9) continue;
            dist[v] = 1;
            q.emplace(v);
        }
    }
    cout << cost * 2;
}