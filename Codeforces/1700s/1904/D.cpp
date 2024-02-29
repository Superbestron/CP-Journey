#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;

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

void solve() {
  cin >> n;
  vi a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  unordered_map<int, stack<int>> mp_l, mp_r;
  bool can = true;
  vi c = a;
  for (int &i : c) i = -i;
  SegmentTree st(b), st2(c);
  for (int i = n - 1; i >= 0; i--) {
    mp_r[a[i]].push(i);
    if (a[i] > b[i]) {
      can = false; break;
    }
  }
  if (!can) {
    cout << "NO\n"; return;
  }
  for (int i = 0; i < n; i++) {
    mp_r[a[i]].pop();
    if (mp_r[a[i]].empty()) mp_r.erase(a[i]);
    if (a[i] != b[i]) {
      can = false;
      if (mp_l.count(b[i])) {
        int idx = mp_l[b[i]].top();
        auto [mn, tmp] = st.RMQ(idx + 1, i);
        auto [mx, tmp2] = st2.RMQ(idx + 1, i);
        mx = -mx;
        if (mn >= b[i] && mx <= b[i]) can = true;
      }
      if (mp_r.count(b[i])) {
        int idx = mp_r[b[i]].top();
        auto [mn, tmp] = st.RMQ(i, idx - 1);
        auto [mx, tmp2] = st2.RMQ(i, idx - 1);
        mx = -mx;
        if (mn >= b[i] && mx <= b[i]) can = true;
      }
      if (!can) {
        break;
      }
    }
    mp_l[a[i]].push(i);
  }
  if (can) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
