#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x, y;
    string loc;
    int arr[8][8];
    int directions[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                            {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
    cin >> n;
    while (n--) {
        cin >> loc;
        x = loc[1] - '1';
        y = loc[0] - 'a';
        memset(arr, -1, sizeof arr);
        arr[x][y] = 0;
        queue<pair<int, int>> q;
        vector<pair<int, int>> v;
        int max = 0;
        q.emplace(x, y);
        while (!q.empty()) {
            auto p = q.front(); q.pop();
            for (auto& direction : directions) {
                int new_x = p.first + direction[0];
                int new_y = p.second + direction[1];
                if (new_x < 0 || new_x >= 8 || new_y < 0 || new_y >= 8) continue;
                if (arr[new_x][new_y] != -1) continue;
                arr[new_x][new_y] = arr[p.first][p.second] + 1;
                q.emplace(new_x, new_y);
                if (arr[new_x][new_y] > max) {
                    max = arr[new_x][new_y];
                    v.clear();
                    v.emplace_back(new_x, new_y);
                } else if (arr[new_x][new_y] == max) {
                    v.emplace_back(new_x, new_y);
                }
            }
        }
        cout << max << ' ';
        auto cmp = [](auto& p1, auto& p2) {
            if (p1.first == p2.first) return p1.second < p2.second;
            return p1.first > p2.first;
        };
        sort(v.begin(), v.end(), cmp);
        for (auto& p : v) {
            cout << static_cast<char>(p.second + 'a') << static_cast<char>(p.first + '1') << ' ';
        }
        cout << '\n';
    }
}