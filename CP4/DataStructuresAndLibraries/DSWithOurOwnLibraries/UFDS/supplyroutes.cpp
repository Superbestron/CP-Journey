#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;

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
  int N, M, Q, l, r, t, u, v;
  cin >> N >> M >> Q;
  vi a(N - 1);
  set<ii> roads;
  viii queries;
  for (int i = 0; i < M; i++) {
    cin >> l >> r;
    roads.emplace(min(l, r), max(l, r));
  }
  for (int i = 0; i < Q; i++) {
    cin >> t >> u >> v;
    queries.emplace_back(t, u, v);
    if (t == 0) roads.erase({min(u, v), max(u, v)});
  }
  vi output;
  UnionFind ufds(N);
  for (auto &[l, r] : roads) ufds.unionSet(l, r);
  for (int i = Q - 1; i >= 0; i--) {
    auto &[t, u, v] = queries[i];
    if (t == 0) ufds.unionSet(u, v);
    else output.push_back(ufds.isSameSet(u, v));
  }
  for (auto it = output.rbegin(); it != output.rend(); it++) {
    if (*it) cout << "safe\n";
    else cout << "unsafe\n";
  }
}
