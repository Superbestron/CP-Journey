#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, r;
    cin >> c >> r;
    string pic[r];
    int ans = 0, dist[r][c];
    for (int i = 0; i < r; i++) cin >> pic[i];
    int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    queue<pair<int, int>> q;
    memset(dist, -1, sizeof dist);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (pic[i][j] != 'P') continue;
            // find CCs
            dist[i][j] = 0;
            q.emplace(i, j);
            while (!q.empty()) {
                pair<int, int> u = q.front();
                q.pop();
                vector<pair<int, int>> temp;
                bool trap = false;
                for (auto& [add_r, add_c] : directions) {
                    int new_r = add_r + u.first;
                    int new_c = add_c + u.second;
                    if (new_r < 0 || new_r >= r || new_c < 0 || new_c >= c) continue;
                    if (pic[new_r][new_c] == '#' || dist[new_r][new_c] != -1) continue;
                    if (pic[new_r][new_c] == 'T') {
                        trap = true;
                        break;
                    }
                    temp.emplace_back(new_r, new_c);
                }
                if (!trap) {
                    for (auto& p : temp) {
                        q.emplace(p);
                        dist[p.first][p.second] = dist[u.first][u.second] + 1;
                        if (pic[p.first][p.second] == 'G') ans++;
                    }
                }
            }
            cout << ans;
            return 0;
        }
    }
}
