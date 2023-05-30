#include <bits/stdc++.h>

using namespace std;

unordered_map<int, unordered_set<int>> AL, FAL;
unordered_set<int> ans;
// 1 is has_error_left
bool visited[2][1001];

void dfs(int u, bool has_error_left) {
    if (visited[has_error_left][u]) return;
    visited[has_error_left][u] = true;
    if (has_error_left) {
        // make error
        for (int v : AL[u]) {
            dfs(v, false);
        }
    }
    // don't make error
    if (FAL[u].empty()) ans.insert(u);
    for (int v : FAL[u]) {
        dfs(v, has_error_left);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, a, b;
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        if (a < 0) FAL[-a].insert(b);
        else AL[a].insert(b);
    }
    memset(visited, false, sizeof visited);
    dfs(1, true);
    cout << ans.size() << '\n';
}