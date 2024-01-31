#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

enum { EXPLORED = 0, VISITED = 1, UNVISITED = -1 };

vi dfs_num, dfs_parent, dist;
vector<vi> AL;
int entry = -1;

void cycleCheck(int u) { // check edge properties
    dfs_num[u] = EXPLORED; // color u as EXPLORED
    for (auto v : AL[u]) { // C++17 style, w ignored
        if (dfs_num[v] == UNVISITED) { // EXPLORED->UNVISITED
            dfs_parent[v] = u; // a tree edge u->v
            cycleCheck(v);
        } else if (dfs_num[v] == EXPLORED) { // EXPLORED->EXPLORED
            if (v != dfs_parent[u]) // differentiate them
                entry = v;
        }
    }
    dfs_num[u] = VISITED; // color u as VISITED/DONE
}

void bfs(int s) {
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : AL[u]) {
            if (dist[v] != 1e9) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, a, b, l, r;
    cin >> t;
    while (t--) {
        cin >> n >> a >> b;
        a--; b--;
        AL.assign(n, {});
        for (int i = 0; i < n; i++) {
            cin >> l >> r;
            l--; r--;
            AL[l].push_back(r);
            AL[r].push_back(l);
        }
        if (a == b) {
            cout << "NO\n";
            continue;
        }
        dfs_num.assign(n, UNVISITED);
        dfs_parent.assign(n, UNVISITED);
        cycleCheck(b);
        dist.assign(n, 1e9);
        bfs(a);
        int distForA = dist[entry];
        dist.assign(n, 1e9);
        bfs(b);
        int distForB = dist[entry];
        if (distForA <= distForB) cout << "NO\n";
        else cout << "YES\n";
    }
}