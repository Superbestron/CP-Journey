#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, w, h;
    cin >> T;
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (T--) {
        cin >> w >> h;
        string arr[h];
        queue<tuple<int, int, bool>> q;
        for (int i = 0; i < h; i++) cin >> arr[i];
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (arr[i][j] == '@') {
                    q.emplace(i, j, true); break;
                }
            }
        }
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (arr[i][j] == '*') {
                    q.emplace(i, j, false);
                }
            }
        }
        int time = 1;
        bool printed = false;
        while (!q.empty() && !printed) {
            int size = q.size();
            while (size-- && !printed) {
                auto [x, y, is_me] = q.front();
                q.pop();
                if (is_me) {
                    if (arr[x][y] == '*') continue; // this position might not be safe when the fire comes
                    for (auto& direction : directions) {
                        int new_x = x + direction[0];
                        int new_y = y + direction[1];
                        if (new_x < 0 || new_x >= h || new_y < 0 || new_y >= w) {
                            // win!
                            cout << time << '\n';
                            printed = true;
                            break;
                        }
                        if (arr[new_x][new_y] != '.') continue; // only go to unvisited location
                        arr[new_x][new_y] = '@';
                        q.emplace(new_x, new_y, is_me);
                    }
                } else {
                    for (auto& direction : directions) {
                        int new_x = x + direction[0];
                        int new_y = y + direction[1];
                        if (new_x < 0 || new_x >= h || new_y < 0 || new_y >= w) continue;
                        if (arr[new_x][new_y] != '.' && arr[new_x][new_y] != '@') continue; // only burn non-wall positions
                        arr[new_x][new_y] = '*';
                        q.emplace(new_x, new_y, is_me);
                    }
                }
            }
            time++;
        }
        if (!printed) cout << "IMPOSSIBLE\n";
    }
}