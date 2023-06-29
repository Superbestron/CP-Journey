#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, x, y;
    string loc;
    int directions[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                            {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
    cin >> N;
    int arr[N][N];
    string board[N];
    for (int i = 0; i < N; i++) {
        cin >> board[i];
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 'K') {
                x = i; y = j; break;
            }
        }
    }
    memset(arr, -1, sizeof arr);
    arr[x][y] = 0;
    queue<pair<int, int>> q;
    q.emplace(x, y);
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        for (auto& direction : directions) {
            int new_x = p.first + direction[0];
            int new_y = p.second + direction[1];
            if (new_x < 0 || new_x >= N || new_y < 0 || new_y >= N) continue;
            if (arr[new_x][new_y] != -1 || board[new_x][new_y] == '#') continue;
            arr[new_x][new_y] = arr[p.first][p.second] + 1;
            q.emplace(new_x, new_y);
        }
    }
    cout << arr[0][0];
}