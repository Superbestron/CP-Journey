#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

int t, n, m;

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

// sort by decreasing weight
auto comp = [](iii &a, iii&b) {
  return get<2>(a) > get<2>(b);
};

int point;
viii edges;
vector<vi> AL;
vector<bool> visited;
vi output;

bool dfs(int u, int p) {
  for (int v : AL[u]) {
    if (v == p) continue;
    // found a cycle
    if (visited[v]) {
      point = v;
      return true;
    }
    visited[v] = true;
    output.push_back(v);
    if (dfs(v, u)) return true;
    output.pop_back();
  }
  return false;
}

void solve() {
  cin >> n >> m;
  edges.assign(m, {});
  for (auto &[u, v, w] : edges) {
    cin >> u >> v >> w;
    u--; v--;
  }
  UnionFind ufds(n);
  visited.assign(n, false);
  AL.assign(n, {});
  sort(edges.begin(), edges.end(), comp);
  int taken, weight;
  for (int i = 0; i < m; i++) {
    auto &[u, v, w] = edges[i];
    if (ufds.isSameSet(u, v)) {
      weight = w;
      taken = i;
    } else {
      ufds.unionSet(u, v);
      AL[u].push_back(v);
      AL[v].push_back(u);
    }
  }
  auto &[u1, v1, w1] = edges[taken];
  AL[u1].push_back(v1);
  AL[v1].push_back(u1);
  vi real_output;
  visited[u1] = true;
  point = -1;
  output.clear();
  output.push_back(u1);
  dfs(u1, -1);
  for (int j = (int) output.size() - 1; j >= 0; j--) {
    real_output.push_back(output[j]);
    if (output[j] == u1) continue;
  }
  cout << weight << ' ' << real_output.size() << '\n';
  for (int j : real_output) cout << j + 1 << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
