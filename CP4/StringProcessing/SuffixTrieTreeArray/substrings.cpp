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

// Find number of repeated substrings

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t; cin >> t;
  string T;
  while (t--) {
    cin >> T;
    T += '$';
    SuffixArray S(T);
//    0  $
//    0  aab$
//    3  aabaab$
//    1  ab$ -> see here that the first 'a' is already counted in the prev '3'
//    2  abaab$ -> so only 'ab' is new
//    0  b$
//    1  baab$
    int ans = 0, minus = 0, prev = -1;
    for (int i = 0; i < S.LCP.size(); i++) {
      if (S.LCP[i] < prev) {
        minus = S.LCP[i]; // means current prefix has smth in common with prefix, avoid double count
        ans += prev - minus;
      }
      prev = S.LCP[i];
    }
    ans += S.LCP.back();
    cout << ans << '\n';
  }
}
