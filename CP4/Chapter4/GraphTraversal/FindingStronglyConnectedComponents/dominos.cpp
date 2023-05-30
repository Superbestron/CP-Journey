#include <bits/stdc++.h>

using namespace std;

enum { UNVISITED = 0, VISITED = 1 };

vector<vector<int>> AL, AL_T;
vector<int> S, dfs_num, scc_index;
vector<bool> scc_has_incoming_outside_edge;
int T, n, m, a, b, num_scc, ans;

void kosaraju(int u, int pass) {
    dfs_num[u] = VISITED;
    vector<int>& neighbours = (pass == 1) ? AL[u] : AL_T[u];
    for (auto& v : neighbours) {
        if (dfs_num[v] == UNVISITED) kosaraju(v, pass);
    }
    if (pass == 1) S.push_back(u);
    else scc_index[u] = num_scc;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        AL.assign(n, vector<int>());
        AL_T.assign(n, vector<int>());
        while (m--) {
            cin >> a >> b;
            a--, b--;
            AL[a].push_back(b);
            AL_T[b].push_back(a);
        }
        scc_index.assign(n, -1);
        dfs_num.assign(n, UNVISITED);
        num_scc = 0;
        ans = 0;
        S.clear();
        for (int u = 0; u < n; u++) {
            if (dfs_num[u] == UNVISITED) kosaraju(u, 1);
        }
        dfs_num.assign(n, UNVISITED);
        for (int i = n - 1; i >= 0; i--) {
            if (dfs_num[S[i]] == UNVISITED) {
                kosaraju(S[i], 2);
                num_scc++;
            }
        }
        scc_has_incoming_outside_edge.assign(num_scc, false);
        for (int u = 0; u < n; u++) {
            for (int v : AL[u]) {
                if (scc_index[u] != scc_index[v]) scc_has_incoming_outside_edge[scc_index[v]] = true;
            }
        }
        for (int i = 0; i < num_scc; i++) {
            if (!scc_has_incoming_outside_edge[i]) ans++;
        }
        cout << ans << '\n';
    }
}