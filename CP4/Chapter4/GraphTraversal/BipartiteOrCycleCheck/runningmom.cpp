#include <bits/stdc++.h>

using namespace std;

enum Indicators { VISITED = 1, EXPLORED = 0, UNVISITED = -1 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, cities = 0;
    string src, dest;
    cin >> n;
    int in_degree[n];
    bool safe[n];
    memset(in_degree, 0, sizeof in_degree);
    memset(safe, true, sizeof safe);
    unordered_map<string, int> name_to_int;
    unordered_map<int, unordered_set<int>> AL;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        cin >> src >> dest;
        if (name_to_int.count(src) == 0) name_to_int[src] = cities++;
        if (name_to_int.count(dest) == 0) name_to_int[dest] = cities++;
        AL[name_to_int[dest]].insert(name_to_int[src]);
        in_degree[name_to_int[src]]++;
    }
    for (int i = 0; i < cities; i++) {
        if (in_degree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        safe[u] = false;
        for (int v : AL[u]) {
            --in_degree[v];
            if (in_degree[v] == 0) q.push(v);
        }
    }
    while (cin >> src) {
        cout << src << ' ' << (safe[name_to_int[src]] ? "safe" : "trapped") << '\n';
    }
}
