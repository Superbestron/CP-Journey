#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, r, ans = 0;
    cin >> r >> c;
    string pic[r];
    int dist[r][c];
    for (int i = 0; i < r; i++) cin >> pic[i];
    int directions[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    queue<pair<int, int>> q;
    memset(dist, -1, sizeof dist);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (pic[i][j] != '#' || dist[i][j] != -1) continue;
            // find CCs
            dist[i][j] = 0;
            q.emplace(i, j);
            while (!q.empty()) {
                pair<int, int> u = q.front();
                q.pop();
                for (auto& [add_r, add_c] : directions) {
                    int new_r = add_r + u.first;
                    int new_c = add_c + u.second;
                    if (new_r < 0 || new_r >= r || new_c < 0 || new_c >= c) continue;
                    if (pic[new_r][new_c] != '#' || dist[new_r][new_c] != -1) continue;
                    dist[new_r][new_c] = dist[u.first][u.second] + 1;
                    q.emplace(new_r, new_c);
                }
            }
            ans++;
        }
    }
    cout << ans << '\n';
}
