#include <bits/stdc++.h>

using namespace std;

int visited[1000][1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int directions[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1},
                            {1, 0}, {1, -1}, {0, -1},{-1, -1}};
    int r, c, n, rs, cs, rd, cd;
    cin >> r >> c;
    string arr[r];
    for (int i = 0; i < c; i++) cin >> arr[i];
    cin >> n;
    while (n--) {
        cin >> rs >> cs >> rd >> cd;
        rs--; cs--; rd--; cd--;
        queue<pair<int, int>> q;
        memset(visited, -1, sizeof visited);
        int dist = 1;
        q.emplace(rs, cs);
        int x = rs, y = cs;
        visited[x][y] = 0;
        // go down current and enqueue all points reached
        while (true) {
            int d = arr[x][y] - '0';
            int next_x = x + directions[d][0];
            int next_y = y + directions[d][1];
            if (next_x < 0 || next_x == r || next_y < 0 || next_y == c) break;
            if (visited[next_x][next_y] != -1) break;
            visited[next_x][next_y] = visited[x][y];
            x = next_x; y = next_y;
            q.emplace(x, y);
        }
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto p = q.front(); q.pop();
                // for each direction follow current till cannot follow
                for (auto& direction : directions) {
                    int next_x = p.first + direction[0];
                    int next_y = p.second + direction[1];
                    if (next_x < 0 || next_x == r || next_y < 0 || next_y == c) continue;
                    if (visited[next_x][next_y] != -1) continue;
                    visited[next_x][next_y] = dist;
                    q.emplace(next_x, next_y);
                    while (true) {
                        int d = arr[next_x][next_y] - '0';
                        int next_next_x = next_x + directions[d][0];
                        int next_next_y = next_y + directions[d][1];
                        if (next_next_x < 0 || next_next_x == r || next_next_y < 0 || next_next_y == c) break;
                        if (visited[next_next_x][next_next_y] != -1) break;
                        visited[next_next_x][next_next_y] = dist;
                        next_x = next_next_x; next_y = next_next_y;
                        q.emplace(next_x, next_y);
                    }
                }
            }
            dist++;
        }
        cout << visited[rd][cd] << '\n';
    }
}