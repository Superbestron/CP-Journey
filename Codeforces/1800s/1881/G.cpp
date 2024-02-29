#include <bits/stdc++.h>
#define LSOne(S) ((S) & -(S))                    // the key operation
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

int t, n, m, q, l, r, x;
string s;

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
      sum = (sum + ft[j]) % 26;
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); } // inc/exclusion

  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, ll v) {
    for (; i < (int) ft.size(); i += LSOne(i))
      ft[i] = (v + ft[i]) % 26;
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

class RUPQ {                                     // RUPQ variant
 private:
  FenwickTree ft;                                // internally use PURQ FT
 public:
  explicit RUPQ(int m) : ft(FenwickTree(m)) {}
  void range_update(int ui, int uj, ll v) {
    ft.update(ui, v);                            // [ui, ui+1, .., m] +v
    ft.update(uj + 1, -v);                         // [uj+1, uj+2, .., m] -v
  }                                              // [ui, ui+1, .., uj] +v
  ll point_query(int i) { return (26 + ft.rsq(i)) % 26; }    // rsq(i) is sufficient
};

void print(set<int> &mp1, set<int>& mp2) {
  for (int i : mp1) cout << i << ' ';
  cout << "->mp1\n";
  for (int i : mp2) cout << i << ' ';
  cout << "->mp2\n-----\n";
}

void solve() {
  cin >> n >> m >> s;
  RUPQ ft(n);
  for (int i = 0; i < n; i++) {
    ft.range_update(i + 1, i + 1, s[i] - 'a');
  }
  set<int> mp, mp2;
  for (int i = 0; i < n - 1; i++) {
    if (s[i] == s[i + 1]) mp.insert(i + 1); // 1 indexing
  }
  for (int i = 0; i < n - 2; i++) {
    if (s[i] == s[i + 2]) mp2.insert(i + 1); // 1 indexing
  }

//  print(mp, mp2);
  for (int i = 0; i < m; i++) {
    cin >> q >> l >> r;
    if (q == 1) {
      cin >> x;
      ft.range_update(l, r, x % 26);
      // update 2 consec same
      if (l != 1) {
        int l1 = ft.point_query(l - 1);
        int l2 = ft.point_query(l);
        if (l1 == l2) mp.insert(l - 1);
        else if (mp.count(l - 1)) mp.erase(l - 1);
      }
      if (r != n) {
        int r1 = ft.point_query(r);
        int r2 = ft.point_query(r + 1);
        if (r1 == r2) mp.insert(r);
        else if (mp.count(r)) mp.erase(r);
      }
      // update a.a same
      if (l > 2) {
        int l1 = ft.point_query(l - 2);
        int l2 = ft.point_query(l);
        if (l1 == l2) mp2.insert(l - 2);
        else if (mp2.count(l - 2)) mp2.erase(l - 2);
      }
      // minimally [l, r] len is 2
      if (l > 1 && l != r) {
        int l1 = ft.point_query(l - 1);
        int l2 = ft.point_query(l + 1);
        if (l1 == l2) mp2.insert(l - 1);
        else if (mp2.count(l - 1)) mp2.erase(l - 1);
      }
      if (r < n - 1) {
        int r1 = ft.point_query(r);
        int r2 = ft.point_query(r + 2);
        if (r1 == r2) mp2.insert(r);
        else if (mp2.count(r)) mp2.erase(r);
      }
      // minimally [l, r] len is 2
      if (r < n && l != r) {
        int r1 = ft.point_query(r - 1);
        int r2 = ft.point_query(r + 1);
        if (r1 == r2) mp2.insert(r - 1);
        else if (mp2.count(r - 1)) mp2.erase(r - 1);
      }
//      print(mp, mp2);
    } else {
      auto it = mp.lower_bound(l);
      auto it2 = mp2.lower_bound(l);
      if (it != mp.end() && *it <= r - 1 || it2 != mp2.end() && *it2 <= r - 2) cout << "NO\n";
      else cout << "YES\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
