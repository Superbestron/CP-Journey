#include <bits/stdc++.h>
using namespace std;

struct MergeSortTree {
  int n;
  vector<vector<int>> tree;

  void build(vector<int> &a, int x, int l, int r) {
    if (l + 1 == r) {
      tree[x] = {a[l]};
      return;
    }

    int m = (l + r) / 2;
    build(a, 2 * x + 1, l, m);
    build(a, 2 * x + 2, m, r);
    merge(tree[2 * x + 1].begin(), tree[2 * x + 1].end(),
          tree[2 * x + 2].begin(), tree[2 * x + 2].end(), back_inserter(tree[x]));
  }

  explicit MergeSortTree(vector<int> &a) : n(a.size()) {
    int SIZE = 1 << (31 - __builtin_clz(n) + bool(__builtin_popcount(n) - 1));
    tree.resize(2 * SIZE - 1);
    build(a, 0, 0, n);
  }

  int count(int lq, int rq, int mn, int mx, int x, int l, int r) {
    if (rq <= l || r <= lq) return 0;
    if (lq <= l && r <= rq) {
      return lower_bound(tree[x].begin(), tree[x].end(), mx)
          - lower_bound(tree[x].begin(), tree[x].end(), mn);
    }

    int m = (l + r) / 2;
    int a = count(lq, rq, mn, mx, 2 * x + 1, l, m);
    int b = count(lq, rq, mn, mx, 2 * x + 2, m, r);
    return a + b;
  }

  // [lq, rq)
  // From lq (inclusive) to rq (exclusive), count how many numbers are within [mn, mx]
  int count(int lq, int rq, int mn, int mx) {
    return count(lq, rq, mn, mx, 0, 0, n);
  }
};

int main() {
  vector<int> a;
  MergeSortTree tree(a);
  int l = 0, n = 10, r = n - 1;
  tree.count(l, r + 1, 0, 5);
}
