#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class SegmentTree {                              // OOP style
 private:
  int n;                                         // n = (int)A.size()
  vi A, st, lazy;                                // the arrays

  int l(int p) { return p << 1; }                 // go to left child
  int r(int p) { return (p << 1) + 1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    if (A[a] > A[b]) return a;
    else return b;
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R)
      st[p] = L;                              // base case
    else {
      int m = (L + R) / 2;
      build(l(p), L, m);
      build(r(p), m + 1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != -1) {                         // has a lazy flag
      st[p] = lazy[p];                           // [L..R] has same value
      if (L != R)                                // not a leaf
        lazy[l(p)] = lazy[r(p)] = lazy[p];       // propagate downwards
      else                                       // L == R, a single index
        A[L] = A[lazy[p]];                          // time to update this
      lazy[p] = -1;                              // erase lazy flag
    }
  }

  int RMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return -1;                        // infeasible
    if ((L >= i) && (R <= j)) return st[p];      // found the segment
    int m = (L + R) / 2;
    return conquer(RMQ(l(p), L, m, i, min(m, j)),
                   RMQ(r(p), m + 1, R, max(i, m + 1), j));
  }

  void update(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      lazy[p] = L;                             // update this
      A[L] = val;
      propagate(p, L, R);                        // lazy propagation
    } else {
      int m = (L + R) / 2;
      update(l(p), L, m, i, min(m, j), val);
      update(r(p), m + 1, R, max(i, m + 1), j, val);
      int lsubtree = (lazy[l(p)] != -1) ? A[lazy[l(p)]] : A[st[l(p)]];
      int rsubtree = (lazy[r(p)] != -1) ? A[lazy[r(p)]] : A[st[r(p)]];
      st[p] = (lsubtree <= rsubtree) ? st[l(p)] : st[r(p)];
    }
  }

 public:
  SegmentTree(int sz) : n(sz), st(4 * n), lazy(4 * n, -1) {}

  SegmentTree(const vi &initialA) : SegmentTree((int) initialA.size()) {
    A = initialA;
    build(1, 0, n - 1);
  }

  void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

  int RMQ(int i, int j) { return RMQ(1, 0, n - 1, i, j); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, y, r;
  while (cin >> n) {
    if (n == 0) break;
    vi a, mp(n, -1);
    for (int i = 0; i < n; i++) {
      cin >> y >> r;
      mp[i] = y;
      a.push_back(r);
    }
    SegmentTree st(a);
    cin >> m;
    for (int i = 0; i < m; i++) {
      cin >> y >> r;
      int x_idx = lower_bound(mp.begin(), mp.end(), y) - mp.begin();
      int y_idx = lower_bound(mp.begin(), mp.end(), r) - mp.begin();
      bool x_exists = x_idx < n && mp[x_idx] == y;
      bool y_exists = y_idx < n && mp[y_idx] == r;

      if (!x_exists && !y_exists) cout << "maybe\n";
      else if (!x_exists) {
        int max_idx = st.RMQ(x_idx, y_idx - 1);
        if (a[max_idx] >= a[y_idx]) cout << "false\n";
        else cout << "maybe\n";
      } else if (!y_exists) {
        int max_idx = st.RMQ(x_idx + 1, y_idx - 1);
        if (a[max_idx] >= a[x_idx]) cout << "false\n";
        else cout << "maybe\n";
      } else {
        int max_idx = st.RMQ(x_idx + 1, y_idx - 1);
        if (a[x_idx] < a[y_idx]) cout << "false\n";
        else if (a[max_idx] >= a[y_idx]) cout << "false\n";
        else {
          if (y_idx - x_idx + 1 == r - y + 1) cout << "true\n";
          else cout << "maybe\n";
        }
      }
    }
    cout << '\n';
  }
}
