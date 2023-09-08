#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<int> vi;

vi taken;
priority_queue<ii> pq;
vector<vector<ii>> AL;

void process(int u) {
    taken[u] = 1;
    for (auto& [v, w] : AL[u]) {
        if (!taken[v]) pq.emplace(-w, -v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, x, y;
    cin >> N;
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    bool board[1000][1000];
    memset(board, false, sizeof board);
    AL.assign(N, vector<tuple<int, int>>());
    vector<vector<pair<int, int>>> dist(1000, vector<pair<int, int>>(1000)); // [dist, src]
    for (auto& i : dist) {
        for (auto& j : i) {
            j = std::move(make_pair(-1, -1));
        }
    }
    queue<iii> q;
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        if (board[x][y]) continue;
        board[x][y] = true;
        q.emplace(x, y, i);
        dist[x][y].first = 0;
        dist[x][y].second = i;
    }
    // do BFS
    vector<unordered_set<int>> edges(N);
    while (!q.empty()) {
        auto [x, y, src] = q.front(); q.pop();
        for (auto& direction : directions) {
            int new_x = x + direction[0];
            int new_y = y + direction[1];
            if (new_x < 0 || new_x == 1000 || new_y < 0 || new_y == 1000) continue;
            // visited
            if (dist[new_x][new_y].first != -1) {
                if (edges[src].count(dist[new_x][new_y].second)) continue;
                AL[src].emplace_back(dist[new_x][new_y].second, dist[x][y].first + dist[new_x][new_y].first + 1);
                edges[src].insert(dist[new_x][new_y].second);
            } else {
                dist[new_x][new_y].first = dist[x][y].first + 1;
                dist[new_x][new_y].second = dist[x][y].second;
                q.emplace(new_x, new_y, dist[new_x][new_y].second);
            }
        }
    }
    taken.assign(N, 0);
    process(0);
    int mst_cost = 0, num_taken = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        w = -w; u = -u;
        if (taken[u]) continue;
        mst_cost += w;
        process(u);
        num_taken++;
        if (num_taken == N - 1) break;
    }
    cout << mst_cost;
}