#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, A, B;
    cin >> n >> m;
    int in_degree[n + 1];
    vector<int> ts;
    unordered_map<int, unordered_set<int>> AL;
    queue<int> q;
    memset(in_degree, 0, sizeof in_degree);
    for (int i = 0; i < m; i++) {
        cin >> A >> B;
        AL[A].insert(B);
        in_degree[B]++;
    }
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ts.push_back(u);
        for (int v : AL[u]) {
            --in_degree[v];
            if (in_degree[v] == 0) q.push(v);
        }
    }
    if (ts.size() == n) {
        for (int i : ts) cout << i << '\n';
    } else cout << "IMPOSSIBLE\n";
}
