#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, H, L, movie;
    cin >> N >> H >> L;
    vector<int> dist(N, 1e9);
    vector<vector<int>> AL(N);
    queue<int> q;
    while (H--) {
        cin >> movie;
        q.push(movie);
        dist[movie] = 0;
    }
    while (L--) {
        int a, b;
        cin >> a >> b;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : AL[u]) {
            if (dist[v] == 1e9) {
                dist[v] = dist[u] + 1;
                q.emplace(v);
            }
        }
    }
    int highest = 0, id;
    for (int i = 0; i < N; i++) {
        if (dist[i] > highest) {
            highest = dist[i];
            id = i;
        }
    }
    cout << id;
}