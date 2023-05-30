#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, m, l, a, b, z;
    cin >> t;
    while (t--) {
        cin >> n >> m >> l;
        unordered_map<int, unordered_map<int, int>> AL(n + 1);
        vector<int> dist(n + 1, 2e9);
        int ans = 0;
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            AL[a][b] = 1;
        }
        queue<int> q;
        for (int i = 0; i < l; i++) {
            cin >> z;
            if (dist[z] != 2e9) continue; // already fallen
            dist[z] = 0;
            q.push(z);
            while (!q.empty()) {
                int curr = q.front(); q.pop();
                for (auto& [v, w] : AL[curr]) {
                    if (dist[v] != 2e9) continue;
                    dist[v] = dist[curr] + 1;
                    q.push(v);
                }
            }
        }
        for (int j = 1; j <= n; j++) {
            if (dist[j] != 2e9) ans++;
        }
        cout << ans << '\n';
    }
}
