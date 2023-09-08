#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef tuple<int, int> ii;
typedef tuple<int, int, int> iii;
typedef tuple<int, int, int, int> iiii;
unordered_set<int> mst_edges, edges_taken, roads_passed;
set<int> edges_blocked;
vector<vector<ii>> AL;
vector<bool> visited;
int n, m, u, v, w;

class UnionFind {                                // OOP style
private:
    vi p, rank;                           // vi p is the key part
public:
    UnionFind(int N) {
        p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);                           // optional speedup
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;                 // i and j are in same set
        int x = findSet(i), y = findSet(j);          // find both rep items
        if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
        p[x] = y;                                    // set x under y
        if (rank[x] == rank[y]) ++rank[y];           // optional speedup
    }
};

bool dfs(int u) {
    visited[u] = true;
    roads_passed.insert(u);
    if (u == n - 1) return true;
    for (auto& [v, v_p] : AL[u]) {
        if (visited[v]) continue;
        if (!mst_edges.count(v_p)) continue;
        edges_taken.insert(v_p);
        bool done = dfs(v);
        if (done) return true;
        edges_taken.erase(v_p);
    }
    roads_passed.erase(u);
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    AL.assign(n, vector<ii>());
    vector<iiii> EL;
    visited.assign(n, false);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        EL.emplace_back(w, u, v, i);
        AL[u].emplace_back(v, i);
        AL[v].emplace_back(u, i);
    }
    sort(EL.begin(), EL.end(), greater());
    UnionFind UF(n);
    int num_taken = 0;
    for (auto& [w, u, v, i] : EL) {
        if (UF.isSameSet(u, v)) continue;
        mst_edges.insert(i);
        UF.unionSet(u, v);
        if (num_taken == n - 1) break;
    }
    dfs(0);
    for (int road : roads_passed) {
        for (auto& [v, i] : AL[road]) {
            if (!edges_taken.count(i)) edges_blocked.insert(i);
        }
    }
    if (edges_blocked.empty()) cout << "none";
    else for (int u : edges_blocked) cout << u << ' ';
}