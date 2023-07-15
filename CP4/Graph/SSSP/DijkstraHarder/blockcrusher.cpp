#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int h, w;
    int directions[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1},
                            {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    while (cin >> h >> w && !(h == 0 && w == 0)) {
        string arr[h];
        for (int i = 0; i < h; i++) cin >> arr[i];
        vector<vector<int>> dist(h, vector<int>(w, 1e9));
        vector<vector<pair<int, int>>> parent(h, vector<pair<int, int>>(w, make_pair(-1, -1)));
        set<tuple<int, int, int>> pq;

        for (int j = 0; j < w; j++) dist[0][j] = arr[0][j] - '0';

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                pq.emplace(dist[i][j], i, j);
            }
        }

        while (!pq.empty()) {
            auto [t, i, j] = *pq.begin();
            pq.erase(pq.begin());
            for (auto& direction : directions) {
                int new_x = direction[0] + i;
                int new_y = direction[1] + j;
                if (new_x < 0 || new_x == h || new_y < 0 || new_y == w) continue;
                int weight = arr[new_x][new_y] - '0';
                if (t + weight >= dist[new_x][new_y]) {
                    continue;
                }
                parent[new_x][new_y] = make_pair(i, j);
                pq.erase(pq.find({dist[new_x][new_y], new_x, new_y}));
                dist[new_x][new_y] = t + weight;
                pq.emplace(dist[new_x][new_y], new_x, new_y);
            }
        }

        pair<int, int> dest = make_pair(h - 1, 0);
        int mini = dist[h - 1][0];
        for (int j = 1; j < w; j++) {
            if (dist[h - 1][j] < mini) {
                mini = dist[h - 1][j];
                dest = make_pair(h - 1, j);
            }
        }

        while (dest.first != -1) {
            arr[dest.first][dest.second] = ' ';
            dest = parent[dest.first][dest.second];
        }

        for (auto& str : arr) cout << str << '\n';
        cout << '\n';
    }
}