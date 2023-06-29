#include <bits/stdc++.h>

using namespace std;

int M, N;
vector<vector<int>> arr, visited;
int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool can(int weight) {
    visited.assign(M, vector<int>(N, false));
    queue<pair<int, int>> q;
    for (int i = 0; i < M; i++) {
        if (arr[i][0] > weight) continue;
        q.emplace(i, 0);
        visited[i][0] = true;
    }
    while (!q.empty()) {
        auto& [x, y] = q.front(); q.pop();
        for (auto& direction : directions) {
            int new_x = x + direction[0];
            int new_y = y + direction[1];
            if (new_x < 0 || new_x >= M || new_y < 0 || new_y >= N) continue;
            if (visited[new_x][new_y]) continue;
            if (arr[new_x][new_y] > weight) continue;
            visited[new_x][new_y] = true;
            q.emplace(new_x, new_y);
        }
    }
    for (int i = 0; i < M; i++) {
        if (visited[i][N - 1]) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> M >> N;
    arr.assign(M, vector<int>(N));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }

    int lo = 0, hi = 1e9;
    while (hi > lo) {
        int mid = (lo + hi) / 2;
        can(mid) ? hi = mid : lo = mid + 1;
    }
    cout << hi;
}