#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c, ans = 0;
    cin >> r >> c;
    string arr[r];
    int dist[1000][1000];
    for (int i = 0; i < r; i++) cin >> arr[i];
    int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    queue<pair<int, int>> q;
    memset(dist, -1, sizeof dist);
    auto bfs = [&](int i, int j) {
        if (dist[i][j] != -1) return;
        q.emplace(i, j);
        dist[i][j] = 0;
        while (!q.empty()) {
            pair<int, int> u = q.front();
            q.pop();
            for (auto& [add_r, add_c] : directions) {
                int new_r = add_r + u.first;
                int new_c = add_c + u.second;
                if (new_r < 0 || new_r >= r || new_c < 0 || new_c >= c) continue;
                if (dist[new_r][new_c] != -1) continue;
                if (arr[new_r][new_c] == '1') {
                    ans++;
                    continue;
                }
                q.emplace(new_r, new_c);
                dist[new_r][new_c] = dist[u.first][u.second];
            }
        }
    };
    for (int i = 0; i < r; i++) {
        if (arr[i][0] == '1') ans++;
        else bfs(i, 0);
        if (arr[i][c - 1] == '1') ans++;
        else bfs(i, c - 1);
    }
    for (int i = 0; i < c; i++) {
        if (arr[0][i] == '1') ans++;
        else bfs(0, i);
        if (arr[r - 1][i] == '1') ans++;
        else bfs(r - 1, i);
    }
    cout << ans;
}
