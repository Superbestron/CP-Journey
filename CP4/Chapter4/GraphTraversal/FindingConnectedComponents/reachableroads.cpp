#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, r, a, b;
    cin >> n;
    while (n--) {
        cin >> m >> r;
        unordered_map<int, unordered_map<int, int>> AL(m);
        vector<int> dist(m, 2e9);
        int ans = 0;
        for (int i = 0; i < r; i++) {
            cin >> a >> b;
            AL[a][b] = 1;
            AL[b][a] = 1;
        }
        queue<int> q;
        for (int i = 0; i < m; i++) {
            if (dist[i] != 2e9) continue;
            dist[i] = 0;
            q.push(i);
            while (!q.empty()) {
                int curr = q.front(); q.pop();
                for (auto& [v, w] : AL[curr]) {
                    if (dist[v] != 2e9) continue;
                    dist[v] = dist[curr] + 1;
                    q.push(v);
                }
            }
            ans++;
        }
        cout << ans - 1 << '\n';
    }
}