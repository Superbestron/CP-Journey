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
    while (p * 2 < (int) ft.size()) p <<= 1;
    int i = 0;
    while (p) {
      if (k > ft[i + p]) {
        k -= ft[i + p];
        i += p;
      }
      p >>= 1;
    }
    return i + 1;
  }
};

vector<vi> AL;
vector<pair<int, int>> entry_exit;
int ctr = 1;

// eulerian tour
void dfs(int u, int p) {
  entry_exit[u].first = ctr++;
  for (int v : AL[u]) {
    if (v != p) {
      dfs(v, u);
    }
  }
  entry_exit[u].second = ctr - 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, Q, P;
  cin >> N >> Q;
  vi C(N);
  vector<vector<ll>> counts(100, vector<ll>(N + 1));
  vector<FenwickTree> v;
  for (int i = 0; i < N; i++) {
    cin >> C[i];
    C[i]--;
  }
  AL.assign(N, {});
  entry_exit.assign(N, {});
  for (int i = 1; i < N; i++) {
    cin >> P;
    P--;
    AL[i].push_back(P);
    AL[P].push_back(i);
  }

  dfs(0, -1);
  for (int i = 0; i < N; i++) {
    int val = C[i];
    counts[val][entry_exit[i].first]++;
  }

  for (int i = 0; i < 100; i++) {
    FenwickTree ft(counts[i]);
    v.push_back(std::move(ft));
  }

  for (int i = 0; i < Q; i++) {
    int K, X;
    cin >> K >> X;
    X--;
    int entry = entry_exit[X].first;
    int exit = entry_exit[X].second;
    if (K == 0) {
      ll ans = 0;
      for (int j = 0; j < 100; j++) {
        ans += v[j].rsq(entry, exit) & 1;
      }
      cout << ans << '\n';
    } else {
      K--;
      int ori_colour = C[X];
      v[ori_colour].update(entry, -1);
      C[X] = K;
      v[K].update(entry, 1);
    }
  }
}
