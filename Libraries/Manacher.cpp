#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ll> vll;

class Manacher {
 private:
  string s;
  int n;
  vi A;

  static vi manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vi p(n + 2);
    int l = 0, r = 1;
    for (int i = 1; i <= n; i++) {
      p[i] = min(r - i, p[l + (r - i)]);
      while( s[i - p[i]] == s[i + p[i]]) {
        p[i]++;
      }
      if(i + p[i] > r) {
        l = i - p[i], r = i + p[i];
      }
    }
    return {begin(p) + 1, end(p) - 1};
  }
 public:
  explicit Manacher(string &s) : s(s) {
    n = s.size();
    string t;
    for (auto c: s) {
      t += string("#") + c;
    }
    A = manacher_odd(t + "#");
  }

  ll num_of_palindromes() {
    vll output(n);
    for (int i = 0; i < n; i++) {
      output[i] = (A[2 * i] - 1) / 2; // even
      output[i] += A[2 * i + 1] / 2; // odd
    }
    return accumulate(output.begin(), output.end(), 0);
  }
};
