#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> dist(n + 1, 1e9), cost(n + 1, 1e9), parent(n + 1, -1);
    vector<vector<int>> AL(n + 1, vector<int>(n + 1, 1e9));
    unordered_map<string, int> name_to_int = {{"English", 0}};
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        string temp;
        cin >> temp;
        name_to_int[temp] = i;
    }
    while (m--) {
        string src, dest;
        int weight;
        cin >> src >> dest >> weight;
        AL[name_to_int[src]][name_to_int[dest]] = weight;
        AL[name_to_int[dest]][name_to_int[src]] = weight;
    }
    dist[0] = 0;
    cost[0] = 0;
    q.emplace(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v <= n; v++) {
            int w = AL[u][v];
            if (w == 1e9) continue;
            int new_cost = w + cost[u];
            if (dist[v] == 1e9) {
                dist[v] = dist[u] + 1;
                cost[v] = new_cost;
                parent[v] = u;
                q.emplace(v);
            } else if (dist[v] == dist[u] + 1) {
                if (AL[v][u] <= AL[v][parent[v]]) {
                    cost[v] = new_cost;
                    parent[v] = u;
                }
            }
        }
    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        if (dist[i] == 1e9) {
            cout << "Impossible";
            return 0;
        }
        cout << parent[i] << ' ' << i << ' ' << AL[parent[i]][i] << '\n';
        ans += AL[parent[i]][i];
    }
    cout << ans;
}