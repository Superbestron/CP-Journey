#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int N, t, a, b;
map<vi, int> vals;

// Use Map to avoid hashing
int encodeTree(int u, int p, vector<vi> &child) {
  vi tuples;
  for (auto &v : child[u]) {
    if (v == p) continue;
    tuples.push_back(encodeTree(v, u, child));
  }
  sort(tuples.begin(), tuples.end());
  if (!vals.count(tuples)) vals[tuples] = vals.size();
  return vals[tuples];
}

void getCentroids(int u, int p, int psize, vector<vi> &child, vi &sz, vi &centroids) {
  if (2 * psize > N) return;
  bool is_centroid = true;
  int sum = 0; // sum of subtree sizes
  int next = -1; // the largest subtree
  for (auto &v : child[u]) {
    if (v == p) continue;
    sum += sz[v];
    if (2 * sz[v] > N)
      is_centroid = false;
    if ((next == -1) || (sz[next] < sz[v]))
      next = v;
  }
  getCentroids(next, u, psize + sum - sz[next] + 1, child, sz, centroids);
  if (is_centroid) centroids.push_back(u);
}

int dfs(int u, int p, vector<vi> &child, vi &sz) {
  int size = 1;
  for (int v : child[u]) {
    if (v == p) continue;
    size += dfs(v, u, child, sz);
  }
  sz[u] = size;
  return size;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> N;
    vector<vi> child1(N), child2(N);
    vi sz1(N), sz2(N);
    vals.clear();
    for (int i = 0; i < N - 1; i++) {
      cin >> a >> b;
      a--; b--;
      child1[a].push_back(b);
      child1[b].push_back(a);
    }
    for (int i = 0; i < N - 1; i++) {
      cin >> a >> b;
      a--; b--;
      child2[a].push_back(b);
      child2[b].push_back(a);
    }
    dfs(0, -1, child1, sz1);
    dfs(0, -1, child2, sz2);
    vi centroids1, centroids2;
    getCentroids(0, 0, 0, child1, sz1, centroids1);
    getCentroids(0, 0, 0, child2, sz2, centroids2);
    if (centroids1.size() != centroids2.size()) cout << "NO\n";
    else {
      vi encodings1, encodings2;
      for (int u : centroids1) encodings1.push_back(encodeTree(u, -1, child1));
      for (int u : centroids2) encodings2.push_back(encodeTree(u, -1, child2));
      sort(encodings1.begin(), encodings1.end());
      sort(encodings2.begin(), encodings2.end());
      if (encodings1 == encodings2) cout << "YES\n";
      else cout << "NO\n";
    }
  }
}
