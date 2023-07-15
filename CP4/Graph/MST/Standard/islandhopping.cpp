#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class UnionFind {                                // OOP style
private:
    vi p, rank;                           // vi p is the key part
public:
    explicit UnionFind(int N) {
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, m;
    cin >> T;
    while (T--) {
        cin >> m;
        vector<pair<double, double>> coords(m);
        int E = m * (m - 1) / 2;
        for (int i = 0; i < m; i++) {
            cin >> coords[i].first >> coords[i].second;
        }
        vector<tuple<double, int, int>> EL;
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                EL.emplace_back(sqrt(pow(coords[i].first - coords[j].first, 2) + pow(coords[i].second - coords[j].second, 2)), i, j);
            }
        }
        sort(EL.begin(), EL.end());                    // sort by w, O(E log E)
        // note: std::tuple has built-in comparison function

        double mst_cost = 0;
        int num_taken = 0;               // no edge has been taken
        UnionFind UF(m);                               // all V are disjoint sets
        // note: the runtime cost of UFDS is very light
        for (int i = 0; i < E; ++i) {                  // up to O(E)
            auto [w, u, v] = EL[i];                      // C++17 style
            if (UF.isSameSet(u, v)) continue;            // already in the same CC
            mst_cost += w;                               // add w of this edge
            UF.unionSet(u, v);                           // link them
            ++num_taken;                                 // 1 more edge is taken
            if (num_taken == m - 1) break;                 // optimization
        }
        cout << fixed << setprecision(3) << mst_cost << '\n';
    }
}