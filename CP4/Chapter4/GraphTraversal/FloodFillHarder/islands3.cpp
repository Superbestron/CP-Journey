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
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (dist[i][j] != -1 || arr[i][j] != 'L') continue;
            q.emplace(i, j);
            dist[i][j] = 0;
            while (!q.empty()) {
                pair<int, int> u = q.front();
                q.pop();
                for (auto &[add_r, add_c]: directions) {
                    int new_r = add_r + u.first;
                    int new_c = add_c + u.second;
                    if (new_r < 0 || new_r >= r || new_c < 0 || new_c >= c) continue;
                    if (dist[new_r][new_c] != -1 || arr[new_r][new_c] == 'W') continue;
                    if (arr[new_r][new_c] == 'C') {
                        arr[new_r][new_c] = 'L';
                    }
                    q.emplace(new_r, new_c);
                    dist[new_r][new_c] = dist[u.first][u.second];
                }
            }
            ans++;
        }
    }
    cout << ans;
}
