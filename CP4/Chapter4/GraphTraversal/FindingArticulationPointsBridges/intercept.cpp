#include <bits/stdc++.h>

using namespace std;

enum { UNVISITED = -1 };

vector<int> dfs_num, dfs_low, dfs_parent, articulation_vertex;
vector<vector<tuple<int, int>>> AL;
vector<unordered_set<int>> RAL, RRAL;
int dfs_number_counter = 0;
int N, M, a, b, w, s, t;

void articulation_point_and_bridge(int u) {
    dfs_low[u] = dfs_num[u] = dfs_number_counter++;
    for (long long v : RRAL[u]) {
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;

            articulation_point_and_bridge(v);

            if (dfs_low[v] >= dfs_num[u]) {
                articulation_vertex[u] = 1;
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
    cin >> N >> M;
    AL.assign(N, vector<tuple<int, int>>());
    RAL.assign(N, unordered_set<int>());
    RRAL.assign(N, unordered_set<int>());
    for (long long i = 0; i < M; i++) {
        cin >> a >> b >> w;
        AL[a].emplace_back(b, w);
        AL[b].emplace_back(a, w);
    }
    cin >> s >> t;

    vector<long long> dist(N, 1e17);
    dist[s] = 0;
    set<tuple<long long, int>> pq;
    for (int u = 0; u < N; u++) pq.emplace(dist[u], u);

    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        for (auto &[v, w]: AL[u]) {
            if (dist[u] + w > dist[v]) continue;
            if (dist[u] + w == dist[v]) {
                RAL[v].insert(u);
                continue;
            }
            RAL[v].clear();
            pq.erase(pq.find({dist[v], v}));
            dist[v] = dist[u] + w;
            RAL[v].insert(u);
            pq.emplace(dist[v], v);
        }
    }

    queue<int> q;
    q.push(t);
    dist.assign(N, 1e9);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : RAL[u]) {
            RRAL[u].insert(v);
            RRAL[v].insert(u);
            if (dist[v] != 1e9) continue;
            dist[v] = 1;
            q.emplace(v);
        }
    }

    dfs_num.assign(N, UNVISITED);
    dfs_low.assign(N, 0);
    dfs_parent.assign(N, -1);
    articulation_vertex.assign(N, 0);

    articulation_point_and_bridge(s);

    articulation_vertex[s] = 1;
    articulation_vertex[t] = 1;

    for (long long i = 0; i < N; i++) {
        if (articulation_vertex[i]) cout << i << ' ';
    }
}