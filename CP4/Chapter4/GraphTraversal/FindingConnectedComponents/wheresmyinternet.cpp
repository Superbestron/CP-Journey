#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b, ans = 0; cin >> n >> m;
    unordered_map<int, unordered_map<int, int>> AL(n + 1);
    vector<int> dist(n + 1, 2e9);
    dist[1] = 0;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        AL[a][b] = 1;
        AL[b][a] = 1;
    }
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        for (auto& [v, w] : AL[curr]) {
            if (dist[v] != 2e9) continue;
            dist[v] = dist[curr] + 1;
            q.push(v);
        }
    }
    bool connected = true;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == 2e9) {
            cout << i << '\n';
            connected = false;
        }
    }
    if (connected) cout << "Connected";
}
