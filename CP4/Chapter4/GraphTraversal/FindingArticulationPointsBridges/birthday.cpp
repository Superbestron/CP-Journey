#include <bits/stdc++.h>

using namespace std;

// Question is a lie..., the graph is actually disconnected, so you need to run the algorithm multiple times

enum { UNVISITED = -1 };

vector<int> dfs_num, dfs_low, dfs_parent;
unordered_map<int, unordered_set<int>> AL;
int dfs_number_counter;

bool articulation_point_and_bridge(int u) {
    bool has = false;
    dfs_low[u] = dfs_num[u] = dfs_number_counter++;
    for (int v : AL[u]) {
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;

            has |= articulation_point_and_bridge(v);

            if (dfs_low[v] > dfs_num[u]) {
                return true;
            }
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != dfs_parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
    return has;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int p, c, a, b;
    while (cin >> p >> c && p != 0 && c != 0) {
        dfs_num.assign(p, UNVISITED);
        dfs_low.assign(p, 0);
        dfs_parent.assign(p, -1);
        dfs_number_counter = 0;
        AL.clear();
        for (int i = 0; i < c; i++) {
            cin >> a >> b;
            AL[a].insert(b);
            AL[b].insert(a);
        }
        bool has_articulation = false;
        for (int i = 0; i < p; i++) {
            if (dfs_num[i] == UNVISITED) has_articulation |= articulation_point_and_bridge(i);
        }
        if (has_articulation) cout << "Yes\n";
        else cout << "No\n";
    }
}