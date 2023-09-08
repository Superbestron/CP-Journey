#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef vector<int> vi;
const int INF = 1e7;

int T, h, w;
string arr[100];
int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void bfs(vector<vi>& dist, pair<int, int>& start) {
    deque<pair<int, int>> q;
    dist[start.first][start.second] = arr[start.first][start.second] == '#';
    q.push_front(start);
    while (!q.empty()) { // main loop
        auto [i, j] = q.front(); q.pop_front(); // shortest unvisited u
        for (auto& direction : directions) { // all edges from u
            int new_i = i + direction[0];
            int new_j = j + direction[1];
            if (new_i < 0 || new_i == h || new_j < 0 || new_j == w || arr[new_i][new_j] == '*') continue;
            if (dist[new_i][new_j] <= dist[i][j] + (arr[new_i][new_j] == '#')) continue; // not improving, skip
            dist[new_i][new_j] = dist[i][j] + (arr[new_i][new_j] == '#'); // relax operation
            if (arr[new_i][new_j] == '#') q.emplace_back(new_i, new_j);
            else q.emplace_front(new_i, new_j);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> h >> w;
        vector<pair<int, int>> prisoners;
        vector<pair<int, int>> end_points;
        for (int i = 0; i < h; i++) {
            cin >> arr[i];
            for (int j = 0; j < w; j++) {
                if (arr[i][j] == '$') prisoners.emplace_back(i, j);
                if ((i == 0 || i == h - 1) && arr[i][j] != '*') {
                    end_points.emplace_back(i, j);
                }
            }
            if (i != 0 && i != h - 1) {
                if (arr[i][0] != '*') end_points.emplace_back(i, 0);
                if (arr[i][w - 1] != '*') end_points.emplace_back(i, w - 1);
            }
        }
        int ans = INF;
        for (auto& end_point : end_points) {
            vector<vi> dist1(h, vi(w, INF)), dist2(h, vi(w, INF)), dist3(h, vi(w, INF));
            bfs(dist1, end_point); bfs(dist2, prisoners[0]); bfs(dist3, prisoners[1]);
            // choose each steiner point
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    if (arr[i][j] == '*') continue;
                    ans = min(ans, dist1[i][j] + dist2[i][j] + dist3[i][j] - 2 * (arr[i][j] == '#'));
                }
            }
        }
        // one more case if no need steiner points
        int min_d2 = INF, min_d3 = INF;
        vector<vi> dist2(h, vi(w, INF)), dist3(h, vi(w, INF));
        bfs(dist2, prisoners[0]); bfs(dist3, prisoners[1]);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if ((i == 0 || i == h - 1) && arr[i][j] != '*') {
                    min_d2 = min(min_d2, dist2[i][j]);
                    min_d3 = min(min_d3, dist3[i][j]);
                }
            }
            if (i != 0 && i != h - 1) {
                min_d2 = min(min_d2, dist2[i][0]);
                min_d3 = min(min_d3, dist3[i][0]);
                min_d2 = min(min_d2, dist2[i][w - 1]);
                min_d3 = min(min_d3, dist3[i][w - 1]);
            }
        }
        cout << min(ans, min_d2 + min_d3) << '\n';
    }
}

