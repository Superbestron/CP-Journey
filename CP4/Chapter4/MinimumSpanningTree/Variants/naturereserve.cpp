#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int> ii;
typedef vector<ii> vii;

int T, N, M, L, S, temp;
vector<int> taken;
vector<vii> AL;
priority_queue<ii, vii, greater<>> pq;

inline void process(int u) {
    taken[u] = 1;
    for (auto& [v, w] : AL[u]) {
        if (!taken[v]) pq.emplace(w, v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> N >> M >> L >> S;
        vector<int> initial;
        while (!pq.empty()) pq.pop();
        while (S--) {
            cin >> temp;
            initial.push_back(--temp);
        }
        AL.assign(N, vii());
        for (int i = 0; i < M; i++) {
            int u, v, energy;
            cin >> u >> v >> energy;
            u--; v--;
            AL[u].emplace_back(v, energy + L);
            AL[v].emplace_back(u, energy + L);
        }
        taken.assign(N, 0);
        for (int u : initial) process(u);
        long long mst_cost = 0, num_taken = 0;
        while (!pq.empty()) {
            auto [w, u] = pq.top(); pq.pop();
            if (taken[u]) continue;
            mst_cost += w;
            process(u);
            num_taken++;
            if (num_taken == N - initial.size()) break;
        }
        cout << mst_cost << '\n';
    }
}