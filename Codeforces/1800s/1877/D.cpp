#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

ll n;
const ll MOD = 998244353;

ll mod(ll a, int m) {                            // returns a (mod m)
  return ((a % m) + m) % m;                        // ensure positive answer
}

ll modPow(ll b, int p, int m) {                  // assume 0 <= b < m
  if (p == 0) return 1;
  ll ans = modPow(b, p / 2, m);                    // this is O(log p)
  ans = mod(ans * ans, m);                         // double it first
  if (p & 1) ans = mod(ans * b, m);                  // *b if p is odd
  return ans;                                    // ans always in [0..m-1]
}

vll getDivisors(ll n) {
  vll ans;
  for (int i = 1; i <= sqrt(n); i++) {
    if (n % i == 0) {
      if (n / i == i) ans.push_back(i);
      else {
        ans.push_back(i);
        ans.push_back(n / i);
      }
    }
  }
  return ans;
}

void solve() {
  cin >> n;
  vll a(n);
  for (ll &i : a) cin >> i;
  vii b;
  for (int i = 0; i < n; i++) {
    b.emplace_back(a[i], i + 1);
  }
  sort(b.begin(), b.end(), greater<>());
  unordered_set<int> factors;
  for (int i = 1; i <= n; i++) factors.insert(i);
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    auto &[num, idx] = b[i];
    vll divisors{getDivisors(idx)};
    int ori_sz = factors.size();
    for (ll div : divisors) {
      factors.erase(div);
    }
    ans += mod(mod(modPow(2, ori_sz, MOD) - modPow(2, factors.size(), MOD), MOD) * num, MOD);
    ans = mod(ans, MOD);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
