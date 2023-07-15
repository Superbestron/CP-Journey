#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    n += 2;
    vector<ii> coords(n);
    vector<int> parent(n);
    vector<vector<ii>> AL(n, vector<ii>());
    for (int i = 0; i < n ; i++) {
        cin >> coords[i].first >> coords[i].second;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = pow(abs(coords[i].first - coords[j].first), 2) + pow(abs(coords[i].second - coords[j].second), 2);
            AL[i].emplace_back(j, dist);
            AL[j].emplace_back(i, dist);
        }
    }
    vector<int> dist(n, 1e9);
    dist[n - 2] = 0;
    set<tuple<int, int>> pq;
    for (int u = 0; u < n; u++) pq.emplace(dist[u], u);

    while (!pq.empty()) {
        auto [t, u] = *pq.begin();
        pq.erase(pq.begin());
        for (auto& [v, w] : AL[u]) {
            if (t + w >= dist[v]) continue;
            parent[v] = u;
            pq.erase(pq.find({dist[v], v}));
            dist[v] = t + w;
            pq.emplace(dist[v], v);
        }
    }

    vector<int> ans;
    int node = parent[n - 1];
    while (node != n - 2) {
        ans.push_back(node);
        node = parent[node];
    }
    if (ans.empty()) cout << "-\n";
    else {
        for (int i = (int) ans.size() - 1; i >= 0; i--) {
            cout << ans[i] << '\n';
        }
    }
}