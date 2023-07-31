#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, D, node_ctr = 0, k = 0;
    long long a, b;
    cin >> N >> M >> D;
    int in_deg[N];
    memset(in_deg, 0, sizeof in_deg);
    unordered_map<long long, int> iden_to_node; // careful with the edge case where id overflows int
    unordered_map<int, int> ranking;
    vector<vector<int>> AL(N, vector<int>());
    vector<int> topo_order, A, L(N);
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        if (!iden_to_node.count(a)) {
            iden_to_node[a] = node_ctr++;

        }
        if (!iden_to_node.count(b)) {
            iden_to_node[b] = node_ctr++;
        }
        in_deg[iden_to_node[b]]++;
        AL[iden_to_node[a]].push_back(iden_to_node[b]);
    }
    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (in_deg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        topo_order.push_back(u);
        q.pop();
        for (int v : AL[u]) {
            in_deg[v]--;
            if (in_deg[v] == 0) q.push(v);
        }
    }
    for (int i = 0; i < topo_order.size(); i++) {
        ranking[topo_order[i]] = i;
    }
    for (int i = 0; i < N; i++) {
        cin >> a;
        if (!iden_to_node.count(a)) continue;
        A.push_back(ranking[iden_to_node[a]]);
    }
    for (int i : A) {
        int pos = lower_bound(L.begin(), L.begin() + k, i) - L.begin();
        L[pos] = i;
        if (pos == k) k = pos + 1;
    }
    cout << 2 * (N - k);
}