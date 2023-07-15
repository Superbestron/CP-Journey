#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

int T, n, t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n >> t;
        vi buttons(n), dist(7200, 1e9);
        queue<int> q;
        for (int i = 0; i < n; i++) {
            cin >> buttons[i];
        }
        dist[0] = 0;
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : buttons) {
                int res = u + v;
                res = max(0, res);
                res = min(res, 3600);
                if (dist[res] == 1e9) {
                    dist[res] = dist[u] + 1;
                    q.push(res);
                }
                if (res == t) break;
            }
        }
        int i;
        for (i = t; i <= 7200; i++) {
            if (dist[i] != 1e9) break;
        }
        cout << dist[i] << ' ' << i - t << '\n';
    }
}