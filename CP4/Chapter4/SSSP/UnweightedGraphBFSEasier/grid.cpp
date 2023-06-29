#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    vector<string> arr(n);
    queue<pair<int, int>> q;
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int i = 0; i < n; i++) cin >> arr[i];
    dist[0][0] = 0;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto& [x, y] = q.front(); q.pop();
        for (auto& direction : directions) {
            int new_x = static_cast<int>(arr[x][y] - '0') * direction[0] + x;
            int new_y = static_cast<int>(arr[x][y] - '0') * direction[1] + y;
            if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m) continue;
            if (dist[new_x][new_y] == 1e9) {
                dist[new_x][new_y] = dist[x][y] + 1;
                q.emplace(new_x, new_y);
            }
            if (new_x == n - 1 && new_y == m - 1) break;
        }
    }
    cout << (dist[n - 1][m - 1] == 1e9 ? -1 : dist[n - 1][m - 1]);
}