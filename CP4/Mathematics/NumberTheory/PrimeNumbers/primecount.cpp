#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef vector<int> vi;

struct _count_primes_struct_t_ {
  vi primes;
  vi mnprimes;
  ll ans;
  ll y;
  vector<pair<pair<ll, int>, char>> queries;

  ll count_primes(ll n) {
    // this y is actually n/y
    // also no logarithms, welcome to reality, this y is the best for n=10^12 or n=10^13
    y = pow(n, 0.64);
    if (n < 100) y = n;

    // linear sieve
    primes.clear();
    mnprimes.assign(y + 1, -1);
    ans = 0;
    for (int i = 2; i <= y; ++i) {
      if (mnprimes[i] == -1) {
        mnprimes[i] = primes.size();
        primes.push_back(i);
      }
      for (int k = 0; k < primes.size(); ++k) {
        int j = primes[k];
        if (i * j > y) break;
        mnprimes[i * j] = k;
        if (i % j == 0) break;
      }
    }
    if (n < 100) return primes.size();
    ll s = n / y;

    for (int p : primes) {
      if (p > s) break;
      ans++;
    }
    // pi(n / y)
    int ssz = ans;

    // F with two pointers
    int ptr = primes.size() - 1;
    for (int i = ssz; i < primes.size(); ++i) {
      while (ptr >= i && (ll)primes[i] * primes[ptr] > n)
        --ptr;
      if (ptr < i) break;
      ans -= ptr - i + 1;
    }

    // phi, store all queries 
    phi(n, ssz - 1);

    sort(queries.begin(), queries.end());
    int ind = 2;
    int sz = primes.size();

    // the order in fenwick will be reversed, because prefix sum in a fenwick is just one query
    fenwick fw(sz);
    for (auto [na, sign] : queries) {
      auto [n, a] = na;
      while (ind <= n)
        fw.add(sz - 1 - mnprimes[ind++], 1);
      ans += (fw.ask(sz - a - 2) + 1) * sign;
    }
    queries.clear();
    return ans - 1;
  }

  void phi(ll n, int a, int sign = 1) {
    if (n == 0) return;
    if (a == -1) {
      ans += n * sign;
      return;
    }
    if (n <= y) {
      queries.emplace_back(make_pair(n, a), sign);
      return;
    }
    phi(n, a - 1, sign);
    phi(n / primes[a], a - 1, -sign);
  }

  struct fenwick {
    vi tree;
    int n;

    fenwick(int n = 0) : n(n) {
      tree.assign(n, 0);
    }

    void add(int i, int k) {
      for (; i < n; i = (i | (i + 1)))
        tree[i] += k;
    }

    int ask(int r) {
      int res = 0;
      for (; r >= 0; r = (r & (r + 1)) - 1)
        res += tree[r];
      return res;
    }
  };
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n; cin >> n;
  ll res = _count_primes_struct_t_().count_primes(n);
  cout << res << '\n';
}
