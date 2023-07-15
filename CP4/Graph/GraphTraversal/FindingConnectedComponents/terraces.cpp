#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, r;
    cin >> c >> r;
    int arr[r][c], dist[r][c];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> arr[i][j];
        }
    }
    int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int ans = r * c;
    queue<pair<int, int>> q;
    memset(dist, -1, sizeof dist);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (dist[i][j] != -1) continue;
            // find CCs
            dist[i][j] = 0;
            q.emplace(i, j);
            int size = 0; bool can = true;
            while (!q.empty()) {
                pair<int, int> u = q.front();
                q.pop();
                size++;
                for (auto& [add_r, add_c] : directions) {
                    int new_r = add_r + u.first;
                    int new_c = add_c + u.second;
                    if (new_r < 0 || new_r >= r || new_c < 0 || new_c >= c) continue;
                    // if same height and visited
                    if (arr[new_r][new_c] == arr[u.first][u.second] && dist[new_r][new_c] != -1) continue;
                    if (arr[new_r][new_c] > arr[u.first][u.second]) continue;
                    else if (arr[new_r][new_c] < arr[u.first][u.second]) {
                        can = false;
                        continue;
                    }
                    dist[new_r][new_c] = dist[u.first][u.second] + 1;
                    q.emplace(new_r, new_c);
                }
            }
            if (!can) ans -= size;
        }
    }
    cout << ans << '\n';
}
