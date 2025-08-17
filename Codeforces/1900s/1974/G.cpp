#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, m, x;

class SegmentTree {
 private:
  const ll FLAG = 2e9;
  int n;                                         // n = (int)A.size()
  vll A;
  vll rsqSt;
  vll setlazy;                                // uncomment if no set op

  int l(int p) { return p << 1; }                 // go to left child
  int r(int p) { return (p << 1) + 1; }              // go to right child

  ll conquerRSQ(ll a, ll b) {
    if (a == FLAG) return b;                       // corner case
    if (b == FLAG) return a;
    return a + b;                                // RSQ modification
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R) {
      rsqSt[p] = A[L];
    } else {
      int m = (L + R) / 2;
      build(l(p), L, m);
      build(r(p), m + 1, R);
      rsqSt[p] = conquerRSQ(rsqSt[l(p)], rsqSt[r(p)]);
    }
  }

  // apply set then update
  void propagate(int p, int L, int R) {
    if (setlazy[p] != FLAG) {
      rsqSt[p] = (R - L + 1) * setlazy[p];              // sum each of [L..R]
      if (L != R) {                               // not a leaf
        setlazy[l(p)] = setlazy[r(p)] = setlazy[p];       // propagate downwards
      } else {                                    // L == R, a single index
        A[L] = setlazy[p];                          // time to update this
      }
      setlazy[p] = FLAG;                              // erase lazy flag
    }
  }

  ll RSQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return 0;                         // infeasible
    if ((L >= i) && (R <= j)) return rsqSt[p];      // found the segment
    int m = (L + R) / 2;
    return conquerRSQ(RSQ(l(p), L, m, i, min(m, j)), RSQ(r(p), m + 1, R, max(i, m + 1), j));
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

      // comment block out if no need rsq
      {
        ll lsubtree2 = (setlazy[l(p)] != FLAG) ? setlazy[l(p)] : rsqSt[l(p)];
        ll rsubtree2 = (setlazy[r(p)] != FLAG) ? setlazy[r(p)] : rsqSt[r(p)];
        rsqSt[p] = lsubtree2 + rsubtree2;
      }
    }
  }

 public:
  SegmentTree(int sz) : n(sz), rsqSt(4 * n), setlazy(4 * n, FLAG) {}

  SegmentTree(const vll &initialA) : SegmentTree((int) initialA.size()) {
    A = initialA;
    build(1, 0, n - 1);
  }

  // ALL ARE [i, j] INCLUSIVE!!
  void set(int i, int j, int val) { set(1, 0, n - 1, i, j, val); }

  ll RSQ(int i, int j) { return RSQ(1, 0, n - 1, i, j); }
};

inline void solve() {
  cin >> m >> x;
  vll a(m), pref(m);
  vii cost_idx;
  int ans = 0;
  for (ll &i : a) cin >> i;
  for (int i = 0; i < m; i++) cost_idx.emplace_back(a[i], i);
  sort(cost_idx.begin(), cost_idx.end());
  for (int i = 0; i < m; i++) pref[i] = x;
  SegmentTree St(pref);
  for (int i = 0; i < m; i++) {
    auto &[cost, idx] = cost_idx[i];
    if (idx == 0) continue;
    // binary search the range sum tree
    int lo = 0, hi = idx - 1;
    while (hi > lo) {
      int mid = lo + (hi - lo + 1) / 2;
      int amt_left = St.RSQ(mid, idx - 1);
      (amt_left >= cost) ? lo = mid : hi = mid - 1;
    }
    int amt_left = St.RSQ(lo, idx - 1);
    if (amt_left < cost) continue;
    int extra = amt_left - cost;
    if (lo + 1 <= idx - 1) St.set(lo + 1, idx - 1, 0);
    St.set(lo, lo, extra);
    ans++;
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
