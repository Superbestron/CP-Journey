#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, int> ii;

const int MOD = 998244353;

class SuffixArray {
 private:
  vi RA;                                             // rank array

  void countingSort(int k) {                         // O(n)
    int maxi = max(300, n);                          // up to 255 ASCII chars
    vi c(maxi, 0);                                   // clear frequency table
    for (int i = 0; i < n; i++)                      // count the frequency
      c[i + k < n ? RA[i + k] : 0]++;                // of each integer rank
    for (int i = 0, sum = 0; i < maxi; i++) {
      int t = c[i]; c[i] = sum; sum += t;
    }
    vi tempSA(n);
    for (int i = 0; i < n; i++)                      // sort RA
      tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    swap(SA, tempSA);                                // update SA
  }

  void constructSA() {                               // can go up to 400k chars
    SA.resize(n);
    iota(SA.begin(), SA.end(), 0);                   // the initial SA
    RA.resize(n);
    for (int i = 0; i < n; i++) RA[i] = T[i];        // initial rankings
    for (int k = 1; k < n; k <<= 1) {                // repeat log_2 n times
      countingSort(k);                               // sort by 2nd item
      countingSort(0);                               // stable-sort by 1st item
      vi tempRA(n);
      int r = 0;
      tempRA[SA[0]] = r;                             // re-ranking process
      for (int i = 1; i < n; i++)                    // compare adj suffixes
        // same pair => same rank r; otherwise, increase r
        tempRA[SA[i]] = ((RA[SA[i]] == RA[SA[i - 1]])
            && (RA[SA[i] + k] == RA[SA[i - 1] + k])) ? r : ++r;
      swap(RA, tempRA);                              // update RA
      if (RA[SA[n - 1]] == n - 1) break;             // nice optimisation
    }
  }

  void computeLCP() {
    vi Phi(n);
    vi PLCP(n);
    PLCP.resize(n);
    Phi[SA[0]] = -1;                                 // default value
    for (int i = 1; i < n; i++)                      // compute Phi in O(n)
      Phi[SA[i]] = SA[i - 1];                        // remember prev suffix
    for (int i = 0, L = 0; i < n; i++) {             // compute PLCP in O(n)
      if (Phi[i] == -1) { PLCP[i] = 0; continue; }   // special case
      while ((i + L < n) && (Phi[i] + L < n) && (T[i + L] == T[Phi[i] + L]))
        L++;                                         // L incr max n times
      PLCP[i] = L;
      L = max(L - 1, 0);                             // L dec max n times
    }
    LCP.resize(n);
    for (int i = 0; i < n; i++)                      // compute LCP in O(n)
      LCP[i] = PLCP[SA[i]];                          // restore PLCP
  }

 public:
  string T;                                          // the input string
  const int n;                                       // the length of T
  vi SA;                                             // Suffix Array
  vi LCP;                                            // of adj sorted suffixes

  SuffixArray(string &initialT) : T(initialT), n(initialT.size()) {
    constructSA();                                   // O(n log n)
    computeLCP();                                    // O(n)
  }

  // extension of class Suffix Array above
  ii stringMatching(string &P) {                     // in O(m log n)
    int m = P.size();                                // usually, m < n
    int lo = 0, hi = n - 1;                          // range = [0 .. n - 1]
    while (lo < hi) {                                // find lower bound
      int mid = (lo + hi) / 2;                       // this is round down
      int res = T.compare(SA[mid], m, P);            // P in suffix SA[mid]?
      (res >= 0) ? hi = mid : lo = mid + 1;          // notice the >= sign
    }
    if (T.compare(SA[lo], m, P) != 0)
      return {-1, -1};                               // if not found
    ii ans; ans.first = lo;
    hi = n - 1;                                      // range = [lo .. n - 1]
    while (lo < hi) {                                // now find upper bound
      int mid = (lo + hi) / 2;
      int res = T.compare(SA[mid], m, P);
      (res > 0) ? hi = mid : lo = mid + 1;           // notice the > sign
    }
    if (T.compare(SA[hi], m, P) != 0) --hi;          // special case
    ans.second = hi;
    return ans;                                      // returns (lb, ub)
  }                                                  // where P is found
};

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

  ll conquerRSQ(ll a, ll b) const {
    if (a == FLAG) return b;                       // corner case
    if (b == FLAG) return a;
    return a + b;                                // RSQ modification
  }

  ll conquerMin(ll a, ll b) const {
    if (a == FLAG) return b;                       // corner case
    if (b == FLAG) return a;
    return min(a, b);                            // RMQ
  }

  // idx only so take in int
  ll conquerMinIdx(int a, int b) {
    if (a == FLAG) return b;                       // corner case
    if (b == FLAG) return a;
    if (A[a] < A[b] || (A[a] == A[b] && a < b)) return a;
    else return b;
  }

  ii conquerMinWithIdx(ll a, ll b, int idxA, int idxB) {
    if (a == FLAG) return {b, idxB};                       // corner case
    if (b == FLAG) return {a, idxA};
    if (a < b) return {a, idxA};
    else if (a > b) return {b, idxB};
    else if (idxA < idxB) return {a, idxA};
    else return {a, idxB};
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
    return conquerMinWithIdx(val1, val2, idx1, idx2);
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

  // ALL ARE [i, j] INCLUSIVE!!
  void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

  void set(int i, int j, int val) { set(1, 0, n - 1, i, j, val); }

  ii RMQ(int i, int j) { return RMQ(1, 0, n - 1, i, j); }

  ll RSQ(int i, int j) { return RSQ(1, 0, n - 1, i, j); }

  ii minElemCnt(int i, int j) { return minElemCnt(1, 0, n - 1, i, j); }
};

ll modMultiply(ll a, ll b, ll c) {
  ll x = 0, y = a % c;
  while (b) {
    if (b & 1) x = (x + y) % c;
    y = (y << 1) % c;
    b >>= 1;
  }
  return x % c;
}

// Abridged problem statement: Find all counts of substrings and its corresponding occurrences

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t; cin >> t;
  string T;
  while (t--) {
    cin >> T;
    int n = T.size(), ans = 0;
    ll substrs = (ll) n * (n + 1) / 2;
    T += '$';
    SuffixArray S(T);
    vll curr;
    for (int i : S.LCP) curr.push_back(i);
    SegmentTree ST(curr);
    for (int i = 0; i < n + 1; i++) {
      substrs -= S.LCP[i];
    }

    auto solve = [&](auto &&f, int l, int r) -> void {
      if (l > r) return;
      auto [val, idx] = ST.RMQ(l, r);
      if (val > 0) {
        int temp = modMultiply(modMultiply(val, r - l + 2, MOD), r - l + 2, MOD);
        ans = (ans + temp) % MOD;
        substrs -= val;
      }

      ST.update(l, r, -val);
      f(f, l, idx - 1);
      f(f, idx + 1, r);
    };

    solve(solve, 0, n);

    ans = (ans + substrs) % MOD;
    cout << ans << '\n';
  }
}
