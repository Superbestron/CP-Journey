#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef tuple<int, int> ii;

class SegmentTree {                              // OOP style
 private:
  int n;                                         // n = (int)A.size()
  vi A, st, st2, lazy;                                // the arrays

  int l(int p) { return p << 1; }                 // go to left child
  int r(int p) { return (p << 1) + 1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return min(a, b);                            // RMQ
  }

  int conquer2(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    if (A[a] < A[b]) return a;
    else return b;
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R) {
      st[p] = A[L];                              // base case
      st2[p] = L;
    } else {
      int m = (L + R) / 2;
      build(l(p), L, m);
      build(r(p), m + 1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
      st2[p] = conquer2(st2[l(p)], st2[r(p)]);
    }
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != -1) {                         // has a lazy flag
      st[p] = lazy[p];                           // [L..R] has same value
      st2[p] = L;
      if (L != R)                                // not a leaf
        lazy[l(p)] = lazy[r(p)] = lazy[p];       // propagate downwards
      else                                       // L == R, a single index
        A[L] = lazy[p];                          // time to update this
      lazy[p] = -1;                              // erase lazy flag
    }
  }

  ii RMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return {-1, -1};                        // infeasible
    if ((L >= i) && (R <= j)) return {st[p], st2[p]};      // found the segment
    int m = (L + R) / 2;
    auto [val1, idx1] = RMQ(l(p), L, m, i, min(m, j));
    auto [val2, idx2] = RMQ(r(p), m + 1, R, max(i, m + 1), j);
    return {conquer(val1, val2), conquer2(idx1, idx2)};
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
      st2[p] = (lsubtree <= rsubtree) ? st2[l(p)] : st2[r(p)];
    }
  }

 public:
  SegmentTree(int sz) : n(sz), st(4 * n), st2(4 * n), lazy(4 * n, -1) {}

  SegmentTree(const vi &initialA) : SegmentTree((int) initialA.size()) {
    A = initialA;
    build(1, 0, n - 1);
  }

  void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

  // [i, j] INCLUSIVE!!
  ii RMQ(int i, int j) { return RMQ(1, 0, n - 1, i, j); }
};

// For RSQ
class SegmentTree {
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
  SegmentTree(int sz) : n(sz), st(4 * n), lazy(4 * n, 0) {}

  SegmentTree(const vi &initialA) : SegmentTree((int) initialA.size()) {
    A = initialA;
    build(1, 0, n - 1);
  }

  void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

  // [i, j] INCLUSIVE!!
  int RSQ(int i, int j) { return RSQ(1, 0, n - 1, i, j); }
};

int main() {
  // 0-based indexing
  vi A = {18, 17, 13, 19, 15, 11, 20, 99};       // make n a power of 2
  SegmentTree st(A);

  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("              A is {18,17,13,19,15,11,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // 13
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // 11
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // 15

  st.update(5, 5, 77);                           // update A[5] to 77
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {18,17,13,19,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // remains 13
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // now 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // remains 15

  st.update(0, 3, 30);                           // update A[0..3] to 30
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30,30,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // now 30
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // remains 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // remains 15

  st.update(3, 3, 7);                            // update A[3] to 7
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30, 7,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // now 7
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // remains 15
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // now 7

  return 0;
}
