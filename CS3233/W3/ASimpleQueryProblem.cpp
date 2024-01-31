#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//~ typedef tuple<int, int> ii;
#define int long long
typedef vector<int> vi;

int t, n, q;

class SegmentTree {                              // OOP style
 private:
  int n;                                         // n = (int)A.size()
  vi A, st, lazy;                                // the arrays

  int l(int p) { return p << 1; }                 // go to left child
  int r(int p) { return (p << 1) + 1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    if (A[a] < A[b]) return a;
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

 public:
  SegmentTree(int sz) : n(sz), st(4 * n), lazy(4 * n, -1) {}

  SegmentTree(const vi &initialA) : SegmentTree((int) initialA.size()) {
    A = initialA;
    build(1, 0, n - 1);
  }

  int RMQ(int i, int j) { return RMQ(1, 0, n - 1, i, j); }
};

void solve() {
  cin >> n;
  vi a(n);
  for (ll &i : a) {
    cin >> i;
    i = -i;
  }
  cin >> q;
  SegmentTree st(a);
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    if (l < 0 || r >= n) cout << "?\n";
    else {
      int idx = st.RMQ(l, r);
      cout << idx << ' ' << -a[idx] << '\n';
    }
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}