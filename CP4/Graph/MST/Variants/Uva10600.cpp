#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef tuple<int, int, int> iii;

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
  int T, N, M;
  cin >> T;
  while (T--) {
    cin >> N >> M;
    vector<iii> EL;
    vector<int> taken;
    for (int i = 0; i < M; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      u--; v--;
      EL.emplace_back(w, u, v);
    }
    sort(EL.begin(), EL.end());                    // sort by w, O(E log E)
    // note: std::tuple has built-in comparison function

    int num_taken = 0, mst_cost = 0, best_cost = 1e9;               // no edge has been taken
    UnionFind UF(N);                               // all V are disjoint sets
    // note: the runtime cost of UFDS is very light
    for (int i = 0; i < M; i++) {
      auto& [w, u, v] = EL[i];                  // up to O(E)
      if (UF.isSameSet(u, v)) continue;            // already in the same CC
      UF.unionSet(u, v);                           // link them
      mst_cost += w;
      ++num_taken;                                 // 1 more edge is taken
      taken.push_back(i);
      if (num_taken == N - 1) break;                 // optimization
    }

    for (int forbidden : taken) {
      num_taken = 0;
      int curr_cost = 0;
      UnionFind UF(N);                               // all V are disjoint sets
      // note: the runtime cost of UFDS is very light
      for (int j = 0; j < M; j++) {
        if (j == forbidden) continue;
        auto& [w, u, v] = EL[j];                  // up to O(E)
        if (UF.isSameSet(u, v)) continue;            // already in the same CC
        UF.unionSet(u, v);                           // link them
        curr_cost += w;
        ++num_taken;                                 // 1 more edge is taken
        if (num_taken == N - 1) break;                 // optimization
      }
      if (num_taken < N - 1) continue;
      best_cost = min(best_cost, curr_cost);
    }
    cout << mst_cost << ' ' << best_cost << '\n';
  }
}
