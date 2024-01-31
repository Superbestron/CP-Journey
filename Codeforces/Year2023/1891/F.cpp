#include <bits/stdc++.h>
#define LSOne(S) ((S) & -(S))                    // the key operation

using namespace std;
typedef long long ll;                            // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

// Important note: 1-based indexing
class FenwickTree {                              // index 0 is not used
 private:
  vll ft;                                        // internal FT is an array
 public:
  explicit FenwickTree(int m) { ft.assign(m+1, 0); }      // create an empty FT

  void build(const vll &f) {
    int m = (int)f.size()-1;                     // note f[0] is always 0
    ft.assign(m+1, 0);
    for (int i = 1; i <= m; ++i) {               // O(m)
      ft[i] += f[i];                             // add this value
      if (i+LSOne(i) <= m)                       // i has parent
        ft[i+LSOne(i)] += ft[i];                 // add to that parent
    }
  }

  explicit FenwickTree(const vll &f) { build(f); }        // create FT based on f

  FenwickTree(int m, const vi &s) {              // create FT based on s
    vll f(m+1, 0);
    for (int i : s) ++f[i];     // do the conversion first in O(n)
    build(f);                                    // in O(m)
  }

  ll rsq(int j) {                                // returns RSQ(1, j)
    ll sum = 0;
    for (; j; j -= LSOne(j))
      sum += ft[j];
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // inc/exclusion

  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, ll v) {
    for (; i < (int)ft.size(); i += LSOne(i))
      ft[i] += v;
  }

  int select(ll k) {                             // O(log m)
    int p = 1;
    while (p*2 < (int)ft.size()) p *= 2;
    int i = 0;
    while (p) {
      if (k > ft[i+p]) {
        k -= ft[i+p];
        i += p;
      }
      p /= 2;
    }
    return i+1;
  }
};

class RUPQ {                                     // RUPQ variant
 private:
  FenwickTree ft;                                // internally use PURQ FT
 public:
  explicit RUPQ(int m) : ft(FenwickTree(m)) {}
  void range_update(int ui, int uj, ll v) {
    ft.update(ui, v);                            // [ui, ui+1, .., m] +v
    ft.update(uj+1, -v);                         // [uj+1, uj+2, .., m] -v
  }                                              // [ui, ui+1, .., uj] +v
  ll point_query(int i) { return ft.rsq(i); }    // rsq(i) is sufficient
};

vector<vector<int>> AL;
vector<pair<int, int>> entryExit;

void dfs(int u, int &idx) {
  entryExit[u].first = idx++;
  for (int v : AL[u]) dfs(v, idx);
  entryExit[u].second = idx++;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, q, type, v, sz;
  cin >> t;
  while (t--) {
    cin >> q;
    vector<int> first;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < q; i++) {
      cin >> type >> v;
      v--;
      if (type == 1) {
        first.push_back(v);
        queries.emplace_back(1, v, 0);
      } else {
        cin >> sz;
        queries.emplace_back(2, v, sz);
      }
    }
    AL.assign(first.size() + 1, {});
    entryExit.assign(first.size() + 1, {});
    for (int i = 0; i < first.size(); i++) {
      AL[first[i]].push_back(i + 1);
    }
    int idx = 1;
    dfs(0, idx);
    RUPQ fenwick_tree(2 * (first.size() + 1));
    sz = 1;
    for (auto& [type, u, x] : queries) {
      if (type == 1) {
        auto& [entry, exit] = entryExit[sz++];
        ll toMinus = fenwick_tree.point_query(entry);
        fenwick_tree.range_update(entry, exit, -toMinus);
      } else {
        auto& [entry, exit] = entryExit[u];
        fenwick_tree.range_update(entry, exit, x);
      }
    }
    for (auto& [entry, exit] : entryExit) {
      cout << fenwick_tree.point_query(entry) << ' ';
    }
    cout << '\n';
  }
}
