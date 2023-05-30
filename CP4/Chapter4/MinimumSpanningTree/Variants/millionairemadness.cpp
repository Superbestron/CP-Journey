//#include <bits/stdc++.h>
//
//using namespace std;
//
//typedef vector<int> vi;
//typedef tuple<int, int, int> iii;
//
//class UnionFind {                                // OOP style
//private:
//    vi p, rank;                           // vi p is the key part
//public:
//    explicit UnionFind(int N) {
//        p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
//        rank.assign(N, 0);                           // optional speedup
//    }
//
//    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
//    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
//
//    void unionSet(int i, int j) {
//        if (isSameSet(i, j)) return;                 // i and j are in same set
//        int x = findSet(i), y = findSet(j);          // find both rep items
//        if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
//        p[x] = y;                                    // set x under y
//        if (rank[x] == rank[y]) ++rank[y];           // optional speedup
//    }
//};
//
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    int N, M;
//    cin >> N >> M;
//    int arr[M][N];
//    vector<iii> EL;
//    for (int i = 0; i < M; i++) {
//        for (int j = 0; j < N; j++) {
//            cin >> arr[i][j];
//        }
//    }
//    for (int i = 0; i < M; i++) {
//        for (int j = 0; j < N; j++) {
//            if (j != N - 1) {
//                EL.emplace_back(arr[i][j + 1])
//            }
//        }
//    }
//    sort(EL.begin(), EL.end());                    // sort by w, O(E log E)
//    // note: std::tuple has built-in comparison function
//
//    int num_taken = 0, mst_cost = 0;               // no edge has been taken
//    UnionFind UF(C);                               // all V are disjoint sets
//    // note: the runtime cost of UFDS is very light
//    for (auto& [w, u, v] : EL) {                  // up to O(E)
//        if (UF.isSameSet(u, v)) continue;            // already in the same CC
//        mst_cost += w;                               // add w of this edge
//        UF.unionSet(u, v);                           // link them
//        ++num_taken;                                 // 1 more edge is taken
//        if (num_taken == C - 1) break;                 // optimization
//    }
//    cout << (mst_cost + C <= M ? "yes" : "no") << '\n';
//}