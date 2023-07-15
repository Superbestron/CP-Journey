#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, a, b;
    cin >> N;
    vector<int> colour(N + 1, 2e9);
    unordered_map<int, unordered_set<int>> AL;
    queue<int> q;
    vector<pair<int, int>> bonds;
    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b;
        AL[a].insert(b);
        AL[b].insert(a);
        bonds.emplace_back(a, b);
    }
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
                    }
                }
            }
        }
    }
    for (auto& [x, y] : bonds) {
        if (colour[x]) cout << 0 << '\n';
        else cout << 1 << '\n';
    }
}
