#include <bits/stdc++.h>

using namespace std;

unordered_map<int, unordered_set<int>> al;
int marbles[10001];
bool visited[10001];

// idea is for a leaf node, greedily take marbles from parents to make it have 1 marble
// (doesn't matter if it originally has negative marbles
// if it has more than 1 marble, greedily give it to parent

long long dfs(int parent, int node) {
    long long ans = 0;
    visited[node] = true;
    for (int child : al[node]) {
        if (!visited[child]) ans += dfs(node, child);
    }
    if (parent == -1) {
        return ans;
    }
    if (marbles[node] == 0) {
        marbles[parent]--;
        ans++;
    } else if (marbles[node] > 1) {
        int moves = marbles[node] - 1;
        marbles[parent] += moves;
        ans += moves;
    } else if (marbles[node] < 0) {
        int moves = -marbles[node] + 1;
        marbles[parent] -= moves;
        ans += moves;
    }
    marbles[node] = 1;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, v, m, d, c;
    while (cin >> n && n != 0) {
        al.clear();
        memset(visited, false, sizeof visited);
        for (int i = 0; i < n; i++) {
            cin >> v >> m >> d;
            marbles[v] = m;
            while (d--) {
                cin >> c;
                al[v].insert(c);
                al[c].insert(v);
            }
        }
        cout << dfs(-1, 1) << '\n';
    }
}