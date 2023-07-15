#include <bits/stdc++.h>

using namespace std;

// Find CCs in one-pass to avoid TLE because there are a lot of queries,

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c, n, r1, c1, r2, c2, ctr = 0;
    cin >> r >> c;
    string arr[r];
    int dist[r][c];
    for (int i = 0; i < r; i++) cin >> arr[i];
    int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    cin >> n;
    queue<pair<int, int>> q;
    memset(dist, -1, sizeof dist);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (dist[i][j] != -1) continue;
            q.emplace(i, j);
            char original = arr[i][j];
            dist[i][j] = ctr;
            while (!q.empty()) {
                pair<int, int> u = q.front();
                q.pop();
                for (auto& [add_r, add_c] : directions) {
                    int new_r = add_r + u.first;
                    int new_c = add_c + u.second;
                    if (new_r < 0 || new_r >= r || new_c < 0 || new_c >= c) continue;
                    if (arr[new_r][new_c] != original || dist[new_r][new_c] != -1) continue;
                    q.emplace(new_r, new_c);
                    dist[new_r][new_c] = dist[u.first][u.second];
                }
            }
            ctr++;
        }
    }
    while (n--) {
        cin >> r1 >> c1 >> r2 >> c2;
        if (dist[r1 - 1][c1 - 1] == dist[r2 - 1][c2 - 1]) {
            if (arr[r1 - 1][c1 - 1] == '1') cout << "decimal\n";
            else cout << "binary\n";
        } else cout << "neither\n";
    }
}
