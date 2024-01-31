#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

int t, n, m, k;
const int MAX_N = 200010;
const int p = 1e9 + 7;                             // p is a prime > MAX_N
ll fact[MAX_N];

ll mod(ll a, int m) {                            // returns a (mod m)
  return ((a % m) + m) % m;                        // ensure positive answer
}

ll modPow(ll b, ll p, int m) {                  // assume 0 <= b < m
  if (p == 0) return 1;
  ll ans = modPow(b, p / 2, m);                    // this is O(log p)
  ans = mod(ans * ans, m);                         // double it first
  if (p & 1) ans = mod(ans * b, m);                  // *b if p is odd
  return ans;                                    // ans always in [0..m-1]
}

ll extEuclid(ll a, ll b, ll &x, ll &y) {    // pass x and y by ref
  ll xx = y = 0;
  ll yy = x = 1;
  while (b) {                                    // repeats until b == 0
    ll q = a / b;
    tie(a, b) = tuple(b, a % b);
    tie(x, xx) = tuple(xx, x - q * xx);
    tie(y, yy) = tuple(yy, y - q * yy);
  }
  return a;                                      // returns gcd(a, b)
}

ll modInverse(ll b, int m) {                   // returns b^(-1) (mod m)
  ll x, y;
  ll d = extEuclid(b, m, x, y);                 // to get b*x + m*y == d
  if (d != 1) return -1;                         // to indicate failure
  // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
  return mod(x, m);
}

ll inv(ll a) {                                   // Fermat's little theorem
  return modPow(a, p - 2, p);                      // modPow in Section 5.8
}

ll C(int n, int k) {                             // O(log p)
  if (n < k) return 0;                           // clearly
  return (((fact[n] * inv(fact[k])) % p) * inv(fact[n - k])) % p;
}

ll fexp(ll b, int p, int m) {
  if (p == 0)return 1;

  ll ans = fexp(b, p >> 1, m);
  ans = mod(ans * ans, m);
  if (p & 1) ans = mod(ans * b, m);
  return ans;
}

void solve() {
  cin >> n >> m >> k;
  ll sum = 0;
  for (int i = 0; i < m; i++) {
    int a, b, f;
    cin >> a >> b >> f;
    sum = mod(sum + f, p);
  }
  ll denom = (ll) n * (n - 1) / 2;
  ll denom_inv = modInverse(denom, p);
  ll base = mod(mod(sum * k, p) * denom_inv, p);
  ll avg_inc = 0;
  for (int i = 1; i <= k; i++) {
    ll extra_sum = mod((ll) i * (i - 1) / 2, p);
    ll prob = mod((C(k, i) * fexp(denom_inv, i, p)), p);
    ll unpicked_prob = fexp(mod((denom - 1) * denom_inv, p), k - i, p);
    prob = mod(prob * unpicked_prob, p);
    avg_inc = mod(avg_inc + mod(extra_sum * prob, p), p);
  }
  ll ans = mod(base + mod(avg_inc * m, p), p);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  fact[0] = 1;
  for (int i = 1; i < MAX_N; ++i)                // O(MAX_N) pre-processing
    fact[i] = (fact[i - 1] * i) % p;                  // fact[i] in [0..p-1]
  while (t--) {
    solve();
  }
}
