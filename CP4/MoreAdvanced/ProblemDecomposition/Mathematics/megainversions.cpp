#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))                    // the key operation

typedef long long ll;                            // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

// Important note: 1-based indexing
class FenwickTree {                              // index 0 is not used
 private:
  vll ft;                                        // internal FT is an array
 public:
  explicit FenwickTree(int m) { ft.assign(m + 1, 0); }      // create an empty FT

  void build(const vll &f) {
    int m = (int) f.size() - 1;                     // note f[0] is always 0
    ft.assign(m + 1, 0);
    for (int i = 1; i <= m; ++i) {               // O(m)
      ft[i] += f[i];                             // add this value
      if (i + LSOne(i) <= m)                       // i has parent
        ft[i + LSOne(i)] += ft[i];                 // add to that parent
    }
  }

  explicit FenwickTree(const vll &f) { build(f); }        // create FT based on f

  FenwickTree(int m, const vi &s) {              // create FT based on s
    vll f(m + 1, 0);
    for (int i : s) ++f[i];     // do the conversion first in O(n)
    build(f);                                    // in O(m)
  }

  ll rsq(int j) {                                // returns RSQ(1, j)
    ll sum = 0;
    for (; j; j -= LSOne(j))
      sum += ft[j];
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); } // inc/exclusion

  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, ll v) {
    for (; i < (int) ft.size(); i += LSOne(i))
      ft[i] += v;
  }

  int select(ll k) {                             // O(log m)
    int p = 1;
    while (p * 2 < (int) ft.size()) p *= 2;
    int i = 0;
    while (p) {
      if (k > ft[i + p]) {
        k -= ft[i + p];
        i += p;
      }
      p /= 2;
    }
    return i + 1;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  ll ans = 0;
  cin >> n;
  vector<int> v(n);
  vector<ll> hi_ans(n), lo_ans(n);
  for (int &i : v) cin >> i;
  FenwickTree ft_hi(n);
  for (int i = n - 1; i >= 0; i--) {
    ll cnt = ft_hi.rsq(v[i] - 1);
    hi_ans[i] = cnt;
    ft_hi.update(v[i], 1);
  }
  FenwickTree ft_lo(n);
  for (int i = 0; i < n; i++) {
    ll cnt = ft_lo.rsq(v[i] + 1, n);
    lo_ans[i] = cnt;
    ft_lo.update(v[i], 1);
  }
  for (int i = 0; i < n; i++) {
    ans += lo_ans[i] * hi_ans[i];
  }
  cout << ans << '\n';
}
