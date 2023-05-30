#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int C, P, X, L, A, B;
    cin >> C >> P >> X >> L;
    int total_deg[C + 1], in_degree[C + 1];
    bool left[C + 1];
    unordered_map<int, unordered_set<int>> AL;
    priority_queue<int, vector<int>, greater<>> pq;
    set<int> s;
    memset(total_deg, 0, sizeof total_deg);
    memset(left, false, sizeof left);
    for (int i = 0; i < P; i++) {
        cin >> A >> B;
        AL[A].insert(B);
        AL[B].insert(A);
        total_deg[A]++;
        in_degree[A] = total_deg[A];
        total_deg[B]++;
        in_degree[B] = total_deg[B];
    }
    pq.push(L);
    while (!pq.empty()) {
        int u = pq.top();
        if (u == X) {
            cout << "leave";
            return 0;
        }
        pq.pop();
        for (int v : AL[u]) {
            --in_degree[v];
            AL[v].erase(u);
            int removed = total_deg[v] - in_degree[v];
            if (!left[v] && removed * 2 >= total_deg[v]) {
                pq.push(v);
                left[v] = true;
            }
        }
    }
    cout << "stay";
}
