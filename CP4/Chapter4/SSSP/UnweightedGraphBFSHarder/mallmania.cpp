#include <bits/stdc++.h>

using namespace std;

int arr[2001][2001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int P, a, s;
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (cin >> P && P != 0) {
        queue<pair<int, int>> q;
        vector<pair<int, int>> v;
        memset(arr, -1, sizeof arr);
        int count = 1;
        while (P--) {
            cin >> a >> s;
            q.emplace(a, s);
            arr[a][s] = 0;
        }
        cin >> P;
        while (P--) {
            cin >> a >> s;
            v.emplace_back(a, s);
        }
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto [x, y] = q.front(); q.pop();
                for (auto& direction : directions) {
                    int new_x = x + direction[0];
                    int new_y = y + direction[1];
                    if (new_x < 0 || new_x == 2001 || new_y < 0 || new_y == 2001) continue;
                    if (arr[new_x][new_y] != -1) continue;
                    q.emplace(new_x, new_y);
                    arr[new_x][new_y] = count;
                }
            }
            count++;
        }
        int mini = INT32_MAX;
        for (auto& [x, y] : v) {
            mini = min(mini, arr[x][y]);
        }
        cout << mini << '\n';
    }
}