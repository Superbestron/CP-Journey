#include <bits/stdc++.h>

using namespace std;

int N, M, a, b, ans = 0;
vector<int> colour(500001, 2e9);
unordered_map<int, unordered_set<int>> AL;
queue<int> q;

// For n connected components, needs n - 1 edges to connect them together
// If it's all bipartite, need 1 more edge, else don't need.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    while (M--) {
        cin >> a >> b;
        AL[a].insert(b);
        AL[b].insert(a);
    }
    bool all_bipartite = true;
    for (int i = 1; i <= N; i++) {
        if (colour[i] == 2e9) {
            q.push(i);
            colour[i] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : AL[u]) {
                    if (colour[v] == 2e9) {
                        colour[v] = 1 - colour[u];
                        q.push(v);
                    } else if (colour[v] == colour[u]) {
                        all_bipartite = false;
                    }
                }
            }
            ans++;
        }
    }
    if (all_bipartite) cout << ans;
    else cout << ans - 1;
}
