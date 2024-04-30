#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ll> vll;

// Applications
// 1. Search the substring (can be solved using Suffix Array)
// 2. Number of distinct substrings in a string O(n^2) (better to use Suffix Array O(n))
// 3. Shortest Compressed representation: find a string t of shortest length such that s
//    can be represented as a concatenation of one of more copies of t
//    e.g. "ababab" -> "ab"

class ZFunction {
 private:
  string s;
  int n;
 public:
  vi z;

  explicit ZFunction(string &s) : s(s), n(s.size()) {
    z.assign(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
      if (i < r) {
        z[i] = min(r - i, z[i - l]);
      }
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
        z[i]++;
      }
      if (i + z[i] > r) {
        l = i;
        r = i + z[i];
      }
    }
  }

  string shortestCompressedRepresentation() const {
    for (int i = 1; i < n; i++) {
      if (n % i == 0) {
        if (i + z[i] == n) {
          return s.substr(0, i);
        }
      }
    }
    return "";
  }
};

int main() {
  string s = "ababababbababababb";
  ZFunction z(s);
  cout << z.shortestCompressedRepresentation() << '\n';
}
