#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

class SegmentTree {
 private:
  const ll FLAG = 2e9;
  int n;                                         // n = (int)A.size()
  vll A, rmqSt, cntMinSt, lazy;                                // the arrays

  int l(int p) { return p << 1; }                 // go to left child
  int r(int p) { return (p << 1) + 1; }              // go to right child

  ll conquerMin(ll a, ll b) {
    if (a == FLAG) return b;                       // corner case
    if (b == FLAG) return a;
    return min(a, b);                            // RMQ
  }

  // cnt is <= 10^6 usually
  ii conquerCntMin(ll val1, ll val2, int cntA, int cntB) {
    if (val1 == FLAG) return {val2, cntB};
    if (val2 == FLAG) return {val1, cntA};
    if (val1 < val2) return {val1, cntA};
    else if (val2 < val1) return {val2, cntB};
    else return {val1, cntA + cntB};
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R) {
      rmqSt[p] = A[L];                              // base case
      cntMinSt[p] = 1;
    } else {
      int m = (L + R) / 2;
      build(l(p), L, m);
      build(r(p), m + 1, R);
      rmqSt[p] = conquerMin(rmqSt[l(p)], rmqSt[r(p)]);
      auto [val, cnt] = conquerCntMin(rmqSt[l(p)], rmqSt[r(p)], cntMinSt[l(p)], cntMinSt[r(p)]);
      cntMinSt[p] = cnt;
    }
  }

  // apply set then update
  void propagate(int p, int L, int R) {
    if (lazy[p] != FLAG) {                          // has a lazy flag
      rmqSt[p] += lazy[p];                          // [L..R] has the same value
      if (L != R) {                               // not a leaf
        if (lazy[l(p)] == FLAG) lazy[l(p)] = lazy[p];  // propagate downwards
        else lazy[l(p)] += lazy[p];
        if (lazy[r(p)] == FLAG) lazy[r(p)] = lazy[p];
        else lazy[r(p)] += lazy[p];
      } else                                       // L == R, a single index
        A[L] += lazy[p];                         // time to update this
      lazy[p] = FLAG;                               // erase lazy flag
    }
  }

  ii minElemCnt(int p, int L, int R, int i, int j) {
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return {FLAG, FLAG};                        // infeasible
    if ((L >= i) && (R <= j)) return {rmqSt[p], cntMinSt[p]};      // found the segment
    int m = (L + R) / 2;
    auto [val1, cnt1] = minElemCnt(l(p), L, m, i, min(m, j));
    auto [val2, cnt2] = minElemCnt(r(p), m + 1, R, max(i, m + 1), j);
    return conquerCntMin(val1, val2, cnt1, cnt2);
  }

  void update(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      if (lazy[p] == FLAG) lazy[p] = val;
      else lazy[p] += val;                            // update this
      propagate(p, L, R);                        // lazy propagation
    } else {
      int m = (L + R) / 2;
      update(l(p), L, m, i, min(m, j), val);
      update(r(p), m + 1, R, max(i, m + 1), j, val);

      ll lsubtree = rmqSt[l(p)]; // if no need setLazy flag
      ll rsubtree = rmqSt[r(p)]; // if no need setLazy flag
      lsubtree += (lazy[l(p)] != FLAG) ? lazy[l(p)] : 0;
      rsubtree += (lazy[r(p)] != FLAG) ? lazy[r(p)] : 0;

      rmqSt[p] = min(lsubtree, rsubtree);

      auto [v, cnt] = conquerCntMin(rmqSt[l(p)], rmqSt[r(p)], cntMinSt[l(p)], cntMinSt[r(p)]);
      cntMinSt[p] = cnt;
    }
  }

 public:
  SegmentTree(int sz) : n(sz), rmqSt(4 * n), cntMinSt(4 * n), lazy(4 * n, FLAG) {}

  SegmentTree(const vll &initialA) : SegmentTree((int) initialA.size()) {
    A = initialA;
    build(1, 0, n - 1);
  }

  void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

  ii minElemCnt(int i, int j) { return minElemCnt(1, 0, n - 1, i, j); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, Q, U, V;
  cin >> N >> Q;
  vll A(N), v(N);
  unordered_set<int> s;

  for (int i = 1; i <= N; i++) {
    cin >> A[i - 1];
    if (s.count(i)) s.erase(i);
    if (A[i - 1] > i) s.insert(A[i - 1]);
    v[i - 1] = s.size();
  }

  SegmentTree st(v);
  cout << st.minElemCnt(0, N - 1).second << '\n';

  for (int i = 0; i < Q; i++) {
    cin >> U >> V; U--; V--;
    int oldUVal = A[U]; oldUVal--;
    int oldVVal = A[V]; oldVVal--;
    if (oldUVal > U) st.update(U, oldUVal - 1, -1);
    if (oldVVal > V) st.update(V, oldVVal - 1, -1);
    if (oldVVal > U) st.update(U, oldVVal - 1, 1);
    if (oldUVal > V) st.update(V, oldUVal - 1, 1);
    swap(A[U], A[V]);
    cout << st.minElemCnt(0, N - 1).second << '\n';
  }
}
