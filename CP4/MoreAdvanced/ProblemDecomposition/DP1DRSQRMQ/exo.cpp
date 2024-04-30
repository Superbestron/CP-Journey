#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;
typedef pair<int, int> ii;

class SegmentTree {
 private:
  const ll FLAG = 2e9;
  int n;                                         // n = (int)A.size()
  vll A;
  vll rsqSt;
  vll rmqSt, rmqIdxSt;
  vll cntMinSt;
  vll lazy;                                   // uncomment if no update op
  vll setlazy;                                // uncomment if no set op

  int l(int p) { return p << 1; }                 // go to left child
  int r(int p) { return (p << 1) + 1; }              // go to right child

  ll conquerRSQ(ll a, ll b) {
    if (a == FLAG) return b;                       // corner case
    if (b == FLAG) return a;
    return a + b;                                // RSQ modification
  }

  ll conquerMin(ll a, ll b) {
    if (a == FLAG) return b;                       // corner case
    if (b == FLAG) return a;
    return min(a, b);                            // RMQ
  }

  // idx only so take in int
  ll conquerMinIdx(int a, int b) {
    if (a == FLAG) return b;                       // corner case
    if (b == FLAG) return a;
    if (A[a] < A[b]) return a;
    else return b;
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
      rmqIdxSt[p] = L;
      cntMinSt[p] = 1;
      rsqSt[p] = A[L];
    } else {
      int m = (L + R) / 2;
      build(l(p), L, m);
      build(r(p), m + 1, R);
      rsqSt[p] = conquerRSQ(rsqSt[l(p)], rsqSt[r(p)]);
      rmqSt[p] = conquerMin(rmqSt[l(p)], rmqSt[r(p)]);
      rmqIdxSt[p] = conquerMinIdx(rmqIdxSt[l(p)], rmqIdxSt[r(p)]);
      auto [val, cnt] = conquerCntMin(rmqSt[l(p)], rmqSt[r(p)], cntMinSt[l(p)], cntMinSt[r(p)]);
      cntMinSt[p] = cnt;
    }
  }

  // apply set then update
  void propagate(int p, int L, int R) {
    if (setlazy[p] != FLAG) {
      rmqSt[p] = setlazy[p];                           // [L..R] has same value
      rmqIdxSt[p] = L;
      cntMinSt[p] = R - L + 1;
      rsqSt[p] = (R - L + 1) * setlazy[p];              // sum each of [L..R]
      if (L != R) {                               // not a leaf
        setlazy[l(p)] = setlazy[r(p)] = setlazy[p];       // propagate downwards
        lazy[l(p)] = lazy[r(p)] = FLAG;              // set overwrites update
      } else {                                    // L == R, a single index
        A[L] = setlazy[p];                          // time to update this
      }
      setlazy[p] = FLAG;                              // erase lazy flag
    }
    if (lazy[p] != FLAG) {                          // has a lazy flag
      rmqSt[p] += lazy[p];                          // [L..R] has the same value
      rsqSt[p] += (R - L + 1) * lazy[p];              // sum each of [L..R]
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

  ii RMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return {FLAG, FLAG};                        // infeasible
    if ((L >= i) && (R <= j)) return {rmqSt[p], rmqIdxSt[p]};      // found the segment
    int m = (L + R) / 2;
    auto [val1, idx1] = RMQ(l(p), L, m, i, min(m, j));
    auto [val2, idx2] = RMQ(r(p), m + 1, R, max(i, m + 1), j);
    return {conquerMin(val1, val2), conquerMinIdx(idx1, idx2)};
  }

  ll RSQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return 0;                         // infeasible
    if ((L >= i) && (R <= j)) return rsqSt[p];      // found the segment
    int m = (L + R) / 2;
    return conquerRSQ(RSQ(l(p), L, m, i, min(m, j)), RSQ(r(p), m + 1, R, max(i, m + 1), j));
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

      // key here is to apply the set op before update op
      ll lsubtree = (setlazy[l(p)] != FLAG) ? setlazy[l(p)] : rmqSt[l(p)];
      ll rsubtree = (lazy[r(p)] != FLAG) ? setlazy[r(p)] : rmqSt[r(p)];
      // ll lsubtree = rmqSt[l(p)]; // if no need setLazy flag
      // ll rsubtree = rmqSt[r(p)]; // if no need setLazy flag
      lsubtree += (lazy[l(p)] != FLAG) ? lazy[l(p)] : 0;
      rsubtree += (lazy[r(p)] != FLAG) ? lazy[r(p)] : 0;

      rmqSt[p] = min(lsubtree, rsubtree);
      rmqIdxSt[p] = (lsubtree <= rsubtree) ? rmqIdxSt[l(p)] : rmqIdxSt[r(p)];

      auto [v, cnt] = conquerCntMin(rmqSt[l(p)], rmqSt[r(p)], cntMinSt[l(p)], cntMinSt[r(p)]);
      cntMinSt[p] = cnt;

      // comment block out if no need rsq
      {
        ll lsubtree2 = (setlazy[l(p)] != FLAG) ? setlazy[l(p)] * max(0, m - L + 1) : rsqSt[l(p)];
        ll rsubtree2 = (setlazy[r(p)] != FLAG) ? setlazy[r(p)] * max(0, R - m) : rsqSt[r(p)];
        lsubtree2 += (lazy[l(p)] != FLAG) ? lazy[l(p)] * max(0, m - L + 1) : 0;
        rsubtree2 += (lazy[r(p)] != FLAG) ? lazy[r(p)] * max(0, R - m) : 0;
        rsqSt[p] = lsubtree2 + rsubtree2;
      }
    }
  }

  void set(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      setlazy[p] = val;                       // update this
      propagate(p, L, R);                        // lazy propagation
    } else {
      int m = (L + R) / 2;
      set(l(p), L, m, i, min(m, j), val);
      set(r(p), m + 1, R, max(i, m + 1), j, val);

      ll lsubtree = (setlazy[l(p)] != FLAG) ? setlazy[l(p)] : rmqSt[l(p)];
      ll rsubtree = (setlazy[r(p)] != FLAG) ? setlazy[r(p)] : rmqSt[r(p)];

      rmqSt[p] = min(lsubtree, rsubtree);
      rmqIdxSt[p] = (lsubtree <= rsubtree) ? rmqIdxSt[l(p)] : rmqIdxSt[r(p)];

      auto [v, cnt] = conquerCntMin(rmqSt[l(p)], rmqSt[r(p)], cntMinSt[l(p)], cntMinSt[r(p)]);
      cntMinSt[p] = cnt;

      // comment block out if no need rsq
      {
        ll lsubtree2 = (setlazy[l(p)] != FLAG) ? setlazy[l(p)] : rsqSt[l(p)];
        ll rsubtree2 = (setlazy[r(p)] != FLAG) ? setlazy[r(p)] : rsqSt[r(p)];
        rsqSt[p] = lsubtree2 + rsubtree2;
      }
    }
  }

 public:
  SegmentTree(int sz) : n(sz), rsqSt(4 * n), rmqSt(4 * n), rmqIdxSt(4 * n), cntMinSt(4 * n),
                        lazy(4 * n, FLAG), setlazy(4 * n, FLAG) {}

  SegmentTree(const vll &initialA) : SegmentTree((int) initialA.size()) {
    A = initialA;
    build(1, 0, n - 1);
  }

  void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

  void set(int i, int j, int val) { set(1, 0, n - 1, i, j, val); }

  // [i, j] INCLUSIVE!!
  ii RMQ(int i, int j) { return RMQ(1, 0, n - 1, i, j); }

  ll RSQ(int i, int j) { return RSQ(1, 0, n - 1, i, j); }

  ii minElemCnt(int i, int j) { return minElemCnt(1, 0, n - 1, i, j); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, m, lim = 0; cin >> n >> m;
  vll a(n);
  for (ll &i : a) {
    cin >> i;
    lim = max(lim, i);
  }
  sort(a.begin(), a.end());
  int lo = 0, hi = lim;
  SegmentTree ST(a);
  auto can = [&](int mid) {
    int idx = upper_bound(a.begin(), a.end(), mid) - a.begin();
    ll sum = ST.RSQ(idx, n - 1) - (ll) (n - idx) * mid;
    return sum >= m;
  };
  while (hi > lo) {
    int mid = lo + (hi - lo + 1) / 2;
    can(mid) ? lo = mid : hi = mid - 1;
  }
  cout << lo << '\n';
}
