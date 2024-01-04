#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef tuple<double, int, int> iii;

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
  int N, S, P;
  cin >> N;
  while (N--) {
    cin >> S >> P;
    vector<iii> EL;
    vector<pair<int, int>> v;
    for (int i = 0; i < P; i++) {
      int x2, y2;
      cin >> x2 >> y2;
      for (int j = 0; j < v.size(); j++) {
        auto &[x1, y1] = v[j];
        double w = hypot(x1 - x2, y1 - y2);
        EL.emplace_back(w, j, i);
      }
      v.emplace_back(x2, y2);
    }
    sort(EL.begin(), EL.end());                    // sort by w, O(E log E)
    // note: std::tuple has built-in comparison function

    int num_taken = 0;               // no edge has been taken
    double D = 0;
    UnionFind UF(P);                               // all V are disjoint sets
    // note: the runtime cost of UFDS is very light
    for (auto& [w, u, v] : EL) {
      if (UF.isSameSet(u, v)) continue;            // already in the same CC
      UF.unionSet(u, v);                           // link them
      ++num_taken;                                 // 1 more edge is taken
      D = max(D, w);
      if (num_taken == P - S) break;                 // optimization
    }

    cout << setprecision(2) << fixed << D << '\n';
  }
}
