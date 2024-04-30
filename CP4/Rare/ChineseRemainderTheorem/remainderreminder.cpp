#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef tuple<int, int, int, int> iiii;
typedef vector<iiii> viiii;
typedef vector<ll> vll;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of p

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

ll general_crt(vll r, vll m) {
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
  int a, b, c, d, e, f, g;
  cin >> a >> b >> c >> d >> e >> f >> g;
  viiii temp;
  for (int i = 1; 2 * i < a; i++) {
    temp.emplace_back(i * (a - 2 * i) * (b - 2 * i), i, a - 2 * i, b - 2 * i);
  }
  sort(temp.begin(), temp.end(), greater<>());
  vll r = {c, d, e}, m;
  for (int i = 0; i < 3; i++) {
    auto &[vol, h, l, w] = temp[i];
    m.push_back(vol);
  }
  int lcms = lcm(m[0], lcm(m[1], m[2]));
  ll ans = general_crt(r, m);
  while (ans < f) ans += lcms;
  cout << ans << '\n';
}
