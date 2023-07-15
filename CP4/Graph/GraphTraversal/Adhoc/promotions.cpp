#include <bits/stdc++.h>

using namespace std;

// to find no possibility of promotion, use DFS with max height

vector<vector<int>> AL(5000, vector<int>()), TAL(5000, vector<int>());
bool visited[5000];
int A, B, E, P, a, b, promotions, ans_A = 0, ans_B = 0, ans_BB = 0;

void dfs(int u) {
    if (visited[u]) return;
    promotions++;
    visited[u] = true;
    for (int v : TAL[u]) dfs(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> A >> B >> E >> P;
    int in_degree[E], curr_in_degree[E];
    memset(in_degree, 0, sizeof(in_degree));
    for (int i = 0; i < P; i++) {
        cin >> a >> b;
        AL[a].push_back(b);
        TAL[b].push_back(a);
        in_degree[b]++;
    }
    queue<int> q;
    // don't promote 1 particular employee per loop
    for (int i = 0; i < E; i++) {
        int employees = 0;
        copy(in_degree, in_degree + E, curr_in_degree);
        for (int j = 0; j < E; j++) {
            if (curr_in_degree[j] == 0) q.push(j);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == i) continue;
            employees++;
            for (int v : AL[u]) {
                curr_in_degree[v]--;
                if (curr_in_degree[v] == 0) q.push(v);
            }
        }
        if (employees < A) ans_A++;
        if (employees < B) ans_B++;
    }
    for (int i = 0; i < E; i++) {
        memset(visited,  false, sizeof(visited));
        promotions = 0;
        dfs(i);
        if (promotions > B) ans_BB++;
    }
    cout << ans_A << '\n' << ans_B << '\n' << ans_BB;
}