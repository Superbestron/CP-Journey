#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef tuple<int, int, int, int> iiii;
typedef pair<int, int> ii;

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

int n, m, q;
int direc[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

inline int convert_to_idx(int x, int y) {
  return x * m + y;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m >> q;
  vector<vi> grid(n, vi(m));
  vector<iiii> strokes;

  for (int i = 0; i < q; i++) {
    int x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1--; x2--; y1--; y2--;
    strokes.emplace_back(x1, y1, x2, y2);
    if (x1 == x2) {
      for (int y = y1; y <= y2; y++) {
        grid[x1][y]++;
      }
    } else {
      for (int x = x1; x <= x2; x++) {
        grid[x][y1]++;
      }
    }
  }

  UnionFind ufds(n * m);
  // find CC of final grid
  queue<ii> que;
  vector<vector<bool>> visited(n, vector<bool>(m));
  vi ans;
  int black_CCs = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] > 0) {
        black_CCs++;
        continue;
      }
      if (visited[i][j]) continue;
      visited[i][j] = true;
      que.emplace(i, j);
      while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();
        ufds.unionSet(convert_to_idx(i, j), convert_to_idx(x, y));
        for (auto &dir : direc) {
          int new_x = x + dir[0];
          int new_y = y + dir[1];
          if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m) continue;
          if (visited[new_x][new_y] || grid[new_x][new_y] > 0) continue;
          visited[new_x][new_y] = true;
          que.emplace(new_x, new_y);
        }
      }
    }
  }
  ans.push_back(ufds.numDisjointSets() - black_CCs);

  // work backwards
  for (int i = q - 1; i >= 1; i--) {
    auto &[x1, y1, x2, y2] = strokes[i];
    vector<ii> v;
    if (x1 == x2) {
      for (int y = y1; y <= y2; y++) {
        grid[x1][y]--;
        if (grid[x1][y] == 0) {
          v.emplace_back(x1, y);
          black_CCs--;
        }
      }
    } else {
      for (int x = x1; x <= x2; x++) {
        grid[x][y1]--;
        if (grid[x][y1] == 0) {
          v.emplace_back(x, y1);
          black_CCs--;
        }
      }
    }
    for (auto &[x, y] : v) {
      for (auto &dir : direc) {
        int new_x = x + dir[0];
        int new_y = y + dir[1];
        if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m) continue;
        if (grid[new_x][new_y] > 0) continue;
        ufds.unionSet(convert_to_idx(x, y), convert_to_idx(new_x, new_y));
      }
    }
    ans.push_back(ufds.numDisjointSets() - black_CCs);
  }

  for (auto it = ans.rbegin(); it != ans.rend(); it++) {
    cout << *it << '\n';
  }
}
