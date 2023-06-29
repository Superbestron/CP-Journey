#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int W, H, G, X, Y, X2, Y2, E, T;
    bool arr[30][30], in_queue[30][30];
    int cnt[30][30], dist[30][30];
    map<pair<int, int>, tuple<int, int, int>> m;
    queue<pair<int, int>> q;
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (cin >> W >> H && !(W == 0 && H == 0)) {
        m.clear();
        cin >> G;
        memset(arr, false, sizeof arr);
        memset(cnt, 0, sizeof cnt);
        fill(dist[0], dist[0] + 900, 1e9);
        memset(in_queue, false, sizeof in_queue);
        while (G--) {
            cin >> X >> Y;
            arr[X][Y] = true; // Gravestones
        }
        cin >> E;
        for (int i = 0; i < E; i++) {
            cin >> X >> Y >> X2 >> Y2 >> T;
            m[make_pair(X, Y)] = make_tuple(X2, Y2, T);
        }
        dist[0][0] = 0;
        while (!q.empty()) q.pop();
        q.emplace(0, 0); // like BFS queue
        in_queue[0][0] = true; // unique to SPFA
        bool has_negative_cycle = false;
        while (!q.empty()) {
            auto p = q.front(); q.pop();
            int i = p.first, j = p.second;
            if (i == W - 1 && j == H - 1) continue;
            in_queue[i][j] = false; // pop from queue
            if (m.count(p)) {
                int new_i = get<0>(m[p]), new_j = get<1>(m[p]), time = get<2>(m[p]);
                if (dist[i][j] + time >= dist[new_i][new_j]) continue; // not improving, skip
                dist[new_i][new_j] = dist[i][j] + time; // relax operation
                cnt[new_i][new_j] = cnt[i][j] + 1;
                if (in_queue[new_i][new_j]) continue; // v already in q, skip
                q.emplace(new_i, new_j);
                in_queue[new_i][new_j] = true; // v is currently in q
                if (cnt[new_i][new_j] == H * W) {
                    has_negative_cycle = true;
                    goto done;
                }
            } else {
                for (auto& direction : directions) { // C++17 style
                    int new_i = i + direction[0];
                    int new_j = j + direction[1];
                    if (new_i < 0 || new_i == W || new_j < 0 || new_j == H) continue;
                    if (arr[new_i][new_j]) continue;
                    if (dist[i][j] + 1 >= dist[new_i][new_j]) continue; // not improving, skip
                    dist[new_i][new_j] = dist[i][j] + 1; // relax operation
                    cnt[new_i][new_j] = cnt[i][j] + 1;
                    if (in_queue[new_i][new_j]) continue; // v already in q, skip
                    q.emplace(new_i, new_j);
                    in_queue[new_i][new_j] = true; // v is currently in q
                    if (cnt[new_i][new_j] == H * W) {
                        has_negative_cycle = true;
                        goto done;
                    }
                }
            }
        }
        done:
        if (has_negative_cycle) cout << "Never\n";
        else if (dist[W - 1][H - 1] == 1e9) cout << "Impossible\n";
        else cout << dist[W - 1][H - 1] << '\n';
    }
}
