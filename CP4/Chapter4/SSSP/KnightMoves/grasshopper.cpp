#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c, gr, gc, lr, lc;
    int arr[100][100];
    int directions[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                            {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
    while (cin >> r >> c >> gr >> gc >> lr >> lc) {
        if (gr == lr && gc == lc) {
            cout << 0 << '\n';
            continue;
        }
        gr--; gc--; lr--; lc--;
        memset(arr, -1, sizeof arr);
        arr[gr][gc] = 0;
        queue<pair<int, int>> q;
        q.emplace(gr, gc);
        bool printed = false;
        while (!q.empty() && !printed) {
            auto p = q.front(); q.pop();
            for (auto& direction : directions) {
                int new_x = p.first + direction[0];
                int new_y = p.second + direction[1];
                if (new_x < 0 || new_x >= r || new_y < 0 || new_y >= c) continue;
                if (arr[new_x][new_y] != -1) continue;
                arr[new_x][new_y] = arr[p.first][p.second] + 1;
                if (new_x == lr && new_y == lc) {
                    cout << arr[new_x][new_y] << '\n';
                    printed = true;
                }
                q.emplace(new_x, new_y);
            }
        }
        if (!printed) cout << "impossible\n";
    }
}