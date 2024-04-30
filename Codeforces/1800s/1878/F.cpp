#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

ll t, n, q, k, x;
ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

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

vll primeFactors(ll N) { // pre-condition, N >= 1
  vll factors;
  for (int i = 0; (i < (int) p.size()) && (p[i] * p[i] <= N); ++i)
    while (N % p[i] == 0) { // found a prime for N
      N /= p[i]; // remove it from N
      factors.push_back(p[i]);
    }
  if (N != 1) factors.push_back(N); // remaining N is a prime
  return factors;
}

bool isPrime(ll N) { // good enough prime test.txt
  if (N < sieve_size) return bs[N]; // O(1) for small primes
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i)
    if (N % p[i] == 0)
      return false;
  return true; // slow if N = large
}

unordered_map<ll, int> primeFactors2(ll N) { // pre-condition, N >= 1
  unordered_map<ll, int> factors;
  if (N == 1) return factors;
  if (isPrime(N)) { factors[N] = 1; return factors; }
  vll prime_facs = primeFactors(N);
  for (ll& x : prime_facs) ++factors[x];
  return factors;
}

void solve() {
  cin >> n >> q;
  ll ori = n;
  int ori_divisors;
  unordered_map<ll, int> mp = primeFactors2(n);
  unordered_map<ll, int> ori_mp = mp;
  int divisors = 1;
  for (auto &[num, v] : mp) {
    divisors *= (v + 1);
  }
  ori_divisors = divisors;


  for (int i = 0; i < q; i++) {
    cin >> k;
    if (k == 1) {
      cin >> x;
      unordered_map<ll, int> temp = primeFactors2(x);
      // O(1)
      for (auto &[num, val] : temp) {
        mp[num] += val;
      }
      divisors = 1;
      for (auto &[num, cnt] : mp) {
        divisors *= (cnt + 1);
      }

      unordered_map<ll, int> divisors_pf = primeFactors2(divisors);
      bool can = true;
      for (auto &[num, cnt] : divisors_pf) {
        if (cnt > mp[num]) {
          can = false;
          break;
        }
      }

      if (can) cout << "YES\n";
      else cout << "NO\n";

    } else {
      mp = ori_mp;
      n = ori;
      divisors = ori_divisors;
    }
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve(10000000);
  cin >> t;
  while (t--) {
    solve();
  }
}
