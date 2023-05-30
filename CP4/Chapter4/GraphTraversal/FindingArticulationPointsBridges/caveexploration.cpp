#include <bits/stdc++.h>

using namespace std;

enum { UNVISITED = -1 };

vector<int> dfs_num, dfs_low, dfs_parent;
vector<pair<int, int>> bridges;
unordered_map<int, unordered_set<int>> AL;
int dfs_number_counter = 0, ans = 0;

void articulation_point_and_bridge(int u) {
    dfs_low[u] = dfs_num[u] = dfs_number_counter++;
    for (int v : AL[u]) {
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;

            articulation_point_and_bridge(v);

            if (dfs_low[v] > dfs_num[u]) {
                bridges.emplace_back(v, u);
            }
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != dfs_parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, a, b;
    cin >> N >> M;
    dfs_num.assign(N, UNVISITED);
    dfs_low.assign(N, 0);
    dfs_parent.assign(N, -1);
    AL.clear();
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        AL[a].insert(b);
        AL[b].insert(a);
    }
    for (int i = 0; i < N; i++) {
        if (dfs_num[i] == UNVISITED) articulation_point_and_bridge(i);
    }
    for (auto& [u, v] : bridges) {
        AL[u].erase(v);
        AL[v].erase(u);
    }
    queue<int> q;
    dfs_num.assign(N, UNVISITED);
    dfs_num[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans++;
        for (int v : AL[u]) {
            if (dfs_num[v] != UNVISITED) continue;
            q.push(v);
            dfs_num[v] = 0;
        }
    }
    cout << ans;
}