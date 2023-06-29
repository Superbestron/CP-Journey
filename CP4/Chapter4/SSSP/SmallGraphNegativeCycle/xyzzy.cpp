#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d, weight, door;
    while (cin >> n && n != -1) {
        vector<bool> in_cycle(n), visited_by_cycles(n);
        vector<int> weights(n), dist(n, 1e9), cnt(n);
        vector<vector<int>> AL(n, vector<int>());
        for (int i = 0; i < n; i++) {
            cin >> weight >> d;
            weights[i] = -weight;
            while (d--) {
                cin >> door; door--;
                AL[i].push_back(door);
            }
        }
        dist[0] = 0;
        for (int i = 0; i < n - 1; i++) {
            bool modified = false;
            for (int u = 0; u < n; u++) {
                if (dist[u] == 1e9) continue;
                for (int v : AL[u]) {
                    int new_weight = dist[u] + weights[v];
                    if (new_weight >= dist[v] || new_weight >= 100) continue;
                    dist[v] = new_weight;
                    modified = true;
                }
            }
            if (!modified) break;
        }

        for (int u = 0; u < n; u++) {
            if (dist[u] == 1e9) continue;
            for (int v : AL[u]) {
                int new_weight = dist[u] + weights[v];
                if (new_weight >= dist[v] || new_weight >= 100) continue;
                in_cycle[v] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            if (!in_cycle[i] || visited_by_cycles[i]) continue;
            visited_by_cycles[i] = true;
            queue<int> t;
            t.push(i);
            while (!t.empty()) {
                int u = t.front(); t.pop();
                for (int v : AL[u]) {
                    if (visited_by_cycles[v]) continue;
                    visited_by_cycles[v] = true;
                    t.push(v);
                }
            }
        }
        if (visited_by_cycles[n - 1] || dist[n - 1] != 1e9) cout << "winnable\n";
        else cout << "hopeless\n";
    }
}
