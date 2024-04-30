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

 public:
  string T;                                          // the input string
  const int n;                                       // the length of T
  vi SA;                                             // Suffix Array
  vi LCP;                                            // of adj sorted suffixes

  SuffixArray(string &initialT) : T(initialT), n(initialT.size()) {
    constructSA();                                   // O(n log n)
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string T;
  while (getline(cin, T)) {
    int n = T.size();
    T += T;
    T += 0x01;
    SuffixArray S(T);
    T.pop_back();
    for (int i = 1; i < S.SA.size(); i++) {
      if (S.SA[i] >= n) continue;
      if (S.SA[i] == 0) cout << T.back();
      else cout << T[S.SA[i] - 1];
    }
    cout << '\n';
  }
}
