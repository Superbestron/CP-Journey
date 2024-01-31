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
    return min(a, b);                            // RMQ
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R)
      st[p] = A[L];                              // base case
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
        A[L] = lazy[p];                          // time to update this
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
      lazy[p] = val;                             // update this
      propagate(p, L, R);                        // lazy propagation
    } else {
      int m = (L + R) / 2;
      update(l(p), L, m, i, min(m, j), val);
      update(r(p), m + 1, R, max(i, m + 1), j, val);
      int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
      int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
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

  // [i, j] INCLUSIVE!!
  int RMQ(int i, int j) { return RMQ(1, 0, n - 1, i, j); }
};

class SegmentTree2 {
 private:
  int n;                                         // n = (int)A.size()
  vi A, st, lazy;                                // the arrays

  int l(int p) { return p << 1; }                 // go to left child
  int r(int p) { return (p << 1) + 1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return a + b;                                // RSQ modification
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R)
      st[p] = A[L];                              // base case
    else {
      int m = (L + R) / 2;
      build(l(p), L, m);
      build(r(p), m + 1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != 0) {                          // has a lazy flag
      st[p] += (R - L + 1) * lazy[p];           // [L..R] has the same value
      if (L != R)                                // not a leaf
        lazy[l(p)] += lazy[p], lazy[r(p)] += lazy[p]; // propagate downwards
      else                                       // L == R, a single index
        A[L] += lazy[p];                         // time to update this
      lazy[p] = 0;                               // erase lazy flag
    }
  }

  int RSQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return 0;                         // infeasible
    if ((L >= i) && (R <= j)) return st[p];      // found the segment
    int m = (L + R) / 2;
    return conquer(RSQ(l(p), L, m, i, min(m, j)),
                   RSQ(r(p), m + 1, R, max(i, m + 1), j));
  }

  void update(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      lazy[p] += val;                            // update this
      propagate(p, L, R);                        // lazy propagation
    } else {
      int m = (L + R) / 2;
      update(l(p), L, m, i, min(m, j), val);
      update(r(p), m + 1, R, max(i, m + 1), j, val);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

 public:
  SegmentTree2(int sz) : n(sz), st(4 * n), lazy(4 * n, 0) {}

  SegmentTree2(const vi &initialA) : SegmentTree2((int) initialA.size()) {
    A = initialA;
    build(1, 0, n - 1);
  }

  void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

  // [i, j] INCLUSIVE!!
  int RSQ(int i, int j) { return RSQ(1, 0, n - 1, i, j); }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K, X, I, V;
  char c;
  while (cin >> N >> K) {
    vi zero_a, neg_a;
    for (int i = 0; i < N; i++) {
      cin >> X;
      if (X != 0) zero_a.push_back(1);
      else zero_a.push_back(0);
      if (X < 0) neg_a.push_back(1);
      else neg_a.push_back(0);
    }
    SegmentTree zero(zero_a);
    SegmentTree2 neg(neg_a);
    for (int i = 0; i < K; i++) {
      cin >> c >> I >> V;
      I--;
      if (c == 'C') {
        if (V == 0) zero.update(I, I, 0);
        else zero.update(I, I, 1);
        if (V < 0 && neg.RSQ(I, I) == 0) {
          neg.update(I, I, 1);
        }
        else if (V >= 0 && neg.RSQ(I, I) == 1) {
          neg.update(I, I, -1);
        }
      } else {
        V--;
        if (zero.RMQ(I, V) == 0) cout << 0;
        else if (neg.RSQ(I, V) % 2 == 0) cout << '+';
        else cout << '-';
      }
    }
    cout << '\n';
  }
}
