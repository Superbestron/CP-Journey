#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;

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

class SparseTable {                              // OOP style
 private:
  vi A, P2, L2;
  vector<vi> SpT;                                // the Sparse Table
 public:
  SparseTable() {}                               // default constructor

  SparseTable(vi &initialA) {                    // pre-processing routine
    A = initialA;
    int n = (int) A.size();
    int L2_n = (int) log2(n) + 1;
    P2.assign(L2_n + 1, 0);
    L2.assign((1 << L2_n) + 1, 0);
    for (int i = 0; i <= L2_n; ++i) {
      P2[i] = (1 << i);                            // to speed up 2^i
      L2[(1 << i)] = i;                            // to speed up log_2(i)
    }
    for (int i = 2; i < P2[L2_n]; ++i)
      if (L2[i] == 0)
        L2[i] = L2[i - 1];                         // to fill in the blanks

    // the initialization phase
    SpT = vector<vi>(L2[n] + 1, vi(n));
    for (int j = 0; j < n; ++j)
      SpT[0][j] = j;                             // RMQ of sub array [j..j]

    // the two nested loops below have overall time complexity = O(n log n)
    for (int i = 1; P2[i] <= n; ++i)             // for all i s.t. 2^i <= n
      for (int j = 0; j + P2[i] - 1 < n; ++j) {      // for all valid j
        int x = SpT[i - 1][j];                     // [j..j+2^(i-1)-1]
        int y = SpT[i - 1][j + P2[i - 1]];             // [j+2^(i-1)..j+2^i-1]
        SpT[i][j] = A[x] <= A[y] ? x : y;
      }
  }

  // returns idx of RMQ of [i, j]
  int RMQ(int i, int j) {
    int k = L2[j - i + 1];                           // 2^k <= (j-i+1)
    int x = SpT[k][i];                           // covers [i..i+2^k-1]
    int y = SpT[k][j - P2[k] + 1];                   // covers [j-2^k+1..j]
    return A[x] <= A[y] ? x : y;
  }
};

// Find longest substring of s that appears at least m times.
// Tiebreak by choosing substring with rightmost occurence

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int m;
  string T;
  while (cin >> m) {
    if (m == 0) break;
    cin >> T;
    if (m == 1) {
      cout << T.size() << ' ' << 0 << '\n';
      continue;
    }
    T += '$';
    SuffixArray S(T);
    int len = 0, idx;
    for (int &i : S.SA) i = -i;
    SparseTable SpT(S.LCP), SpT2(S.SA);
    for (int r = 1; r < (int) T.size() - (m - 2); r++) {
      // consider [r - 1, r + m - 2]
      int mn = S.LCP[SpT.RMQ(r, r + m - 2)];
      if (mn > len) {
        len = mn;
        idx = -S.SA[SpT2.RMQ(r - 1, r + m - 2)]; // find rightmost occurrence
      } else if (mn == len) {
        idx = max(idx, -S.SA[SpT2.RMQ(r - 1, r + m - 2)]);
      }
    }
    if (len == 0) cout << "none\n";
    else cout << len << ' ' << idx << '\n';
  }
}
