#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> iii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int h, w;
    long long v = 0;
    int directions[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1},
                            {1, 0}, {1, -1}, {0, -1},{-1, -1}};
    cin >> h >> w;
    pair<int, int> d;
    priority_queue<iii> pq;
    vector<vector<int>> arr(h, vector<int>(w)), dist(h, vector<int>(w, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> arr[i][j];
        }
    }
    cin >> d.first >> d.second;
    dist[d.first][d.second] = abs(arr[--d.first][--d.second]);
    pq.emplace(dist[d.first][d.second], d.first, d.second);

    while (!pq.empty()) {
        auto [maxi, i, j] = pq.top(); pq.pop();
        if (maxi < dist[i][j]) continue; // inferior
        for (auto& direction : directions) {
            int new_i = i + direction[0];
            int new_j = j + direction[1];
            if (new_i < 0 || new_i == h || new_j < 0 || new_j == w) continue;
            if (arr[new_i][new_j] >= 0) continue; // can't go on land
            int max_flow = min(maxi, abs(arr[new_i][new_j])); // flow is limited by altitude of dest
            if (max_flow <= dist[new_i][new_j]) continue;
            dist[new_i][new_j] = max_flow;
            pq.emplace(dist[new_i][new_j], new_i, new_j);
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            v += dist[i][j];
        }
    }
    cout << v;
}