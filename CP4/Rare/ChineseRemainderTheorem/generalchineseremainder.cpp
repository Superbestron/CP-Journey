#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<ll, ll> ii;
typedef vector<ll> vll;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of p

ll mod(ll a, ll m) {                           // returns a (mod m)
  return ((a % m) + m) % m;                        // ensure positive answer
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

ll modInverse(ll b, ll m) {                   // returns b^(-1) (mod m)
  ll x, y;
  ll d = extEuclid(b, m, x, y);                 // to get b*x + m*y == d
  if (d != 1) return -1;                         // to indicate failure
  // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
  return mod(x, m);
}

ll crt(vll r, vll m) {
  ll mt = accumulate(m.begin(), m.end(), 1LL, multiplies<>());
  ll x = 0;
  for (int i = 0; i < m.size(); ++i) {
    ll a = mod(r[i] * modInverse(mt / m[i], m[i]), m[i]);
    x = mod(x + a * (mt / m[i]), mt);
  }
  return x;
}

void sieve(ll upperbound) { // range = [0..upperbound]
  sieve_size = upperbound + 1; // to include upperbound
  bs.set(); // all 1s
  bs[0] = bs[1] = false; // except index 0+1
  for (ll i = 2; i < sieve_size; ++i)
    if (bs[i]) {
      // cross out multiples of i starting from i*i
      for (ll j = i * i; j < sieve_size; j += i) bs[j] = false;
      p.push_back(i); // add prime i to the list
    }
}

ll fexp(ll b, ll p) {
  if (p == 0) return 1;

  ll ans = fexp(b, p >> 1);
  ans *= ans;
  if (p & 1) ans *= b;
  return ans;
}

vector<ii> prime_factorise(ll n) {
  vector<ii> prime_factors;
  int exp;
  for (ll i = 0; i < p.size() && p[i] * p[i] <= n; i++) {
    if (n % p[i] == 0) {
      exp = 0;
      while (n % p[i] == 0) {
        n /= p[i];
        exp++;
      }
      prime_factors.emplace_back(p[i], exp);
    }
  }
  if (n != 1) prime_factors.emplace_back(n, 1);
  return prime_factors;
}

// Ensure r_i = r_j (mod gcd(m_i, m_j)) for all i, j
bool verify_crt(vll &r, vll &m) {
  for (int i = 0; i < r.size(); ++i) {
    for (int j = i + 1; j < m.size(); ++j) {
      if (mod(r[i], gcd(m[i], m[j])) != mod(r[j], gcd(m[i], m[j]))) {
        return false;
      }
    }
  }
  return true;
}

ll general_crt(vll r, vll m) {
  if (!verify_crt(r, m)) {
    return -1;
  }
  unordered_map<ll, ll> prime_highest_pow;
  unordered_map<ll, ll> S;

  for (int i = 0; i < m.size(); i++) {
    vector<ii> factors = prime_factorise(m[i]);
    for (auto &[p, exp] : factors) {
      if (prime_highest_pow[p] < exp) {
        prime_highest_pow[p] = exp;
        S[p] = r[i] % (fexp(p, exp));
      }
    }
  }

  vll nr, nm;
  for (auto &[p, exp] : prime_highest_pow) {
    nr.push_back(S[p]);
    nm.push_back(fexp(p, exp));
  }

  return crt(nr, nm);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve(10000000);
  ll T, a, n, b, m;
  cin >> T;
  while (T--) {
    cin >> a >> n >> b >> m;
    vll r({a, b});
    vll moduli({n, m});

    ll ans = general_crt(r, moduli);
    if (ans == -1) cout << "no solution\n";
    else cout << ans << ' ' << lcm(n, m) << '\n';
  }
}
