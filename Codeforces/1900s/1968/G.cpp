#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, l, r;
string s;

class KMP {
 private:
  int n, m;
  vi b;                                            // b = back table
  const string T, P;
 public:
  KMP(const string &T, const string &P) : T(T), P(P) {
    n = T.size();
    m = P.size();
    int i = 0, j = -1;
    b.assign(n, 0);
    b[0] = -1;                                     // starting values
    while (i < m) {                                // pre-process P
      while ((j >= 0) && (P[i] != P[j])) j = b[j]; // different, reset j
      ++i; ++j;                                    // same, advance both
      b[i] = j;
    }
  }
  int kmpSearch() {                               // similar as above
    int freq = 0;
    int i = 0, j = 0;                              // starting values
    int prev = -1;
    while (i < n) {                                // search through T
      while ((j >= 0) && (T[i] != P[j])) j = b[j]; // if different, reset j
      ++i;
      ++j;                                    // if same, advance both
      if (j == m) {                                // a match is found
        if (prev + m <= i) {
          ++freq;
          prev = i;
        }
        j = b[j];                                  // prepare j for the next
      }
    }
    return freq;
  }
};

inline void solve() {
  cin >> n >> l >> r >> s;
  vi memo(n, -1);
  for (int i = l; i <= r; i++) {
    if (i == 1) {
      cout << n << ' ';
      continue;
    }
    int max_len = n / i;
    if (max_len == 0) {
      cout << 0 << ' ';
      continue;
    }
    int lo = 0, hi = max_len;
    auto can = [&](int mid) {
      int &ans = memo[mid];
      if (ans != -1) return ans >= i;
      KMP kmp(s, s.substr(0, mid));
      int cnt = kmp.kmpSearch();
      ans = cnt;
      return cnt >= i;
    };
    while (hi > lo) {
      int mid = lo + (hi - lo + 1) / 2;
      can(mid) ? lo = mid : hi = mid - 1;
    }
    cout << lo << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
