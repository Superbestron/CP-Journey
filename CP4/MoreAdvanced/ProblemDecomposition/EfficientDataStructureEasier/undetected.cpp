#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;

class UnionFind {                                // OOP style
 private:
  vi p, rank, setSize;                           // vi p is the key part
  int numSets;
 public:
  explicit UnionFind(int N) {
    p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
    rank.assign(N, 0);                           // optional speedup
    setSize.assign(N, 1);                        // optional feature
    numSets = N;                                 // optional feature
  }

  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  int numDisjointSets() const { return numSets; }      // optional
  int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional

  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items
    if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
    p[x] = y;                                    // set x under y
    if (rank[x] == rank[y]) ++rank[y];           // optional speedup
    setSize[y] += setSize[x];                    // combine set sizes at y
    --numSets;                                   // a union reduces numSets
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, x, y, r;
  cin >> N;
  vector<iii> v;
  UnionFind ufds(N);
  vi left, right;
  for (int i = 0; i < N; i++) {
    cin >> x >> y >> r;
    v.emplace_back(x, y, r);
    if (x - r <= 0) left.push_back(i);
    if (x + r >= 200) right.push_back(i);
  }
  for (int i = 0; i < N; i++) {
    auto &[x1, y1, r1] = v[i];
    for (int j = 0; j < i; j++) {
      auto &[x2, y2, r2] = v[j];
      if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2)) {
        ufds.unionSet(i, j);
      }
    }
    for (int l : left) {
      for (int rt : right) {
        if (ufds.isSameSet(l, rt)) {
          cout << i << '\n';
          return 0;
        }
      }
    }
  }
}
