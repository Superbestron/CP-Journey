#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;

int sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vi p; // compact list of primes

void sieve(int upperbound) { // range = [0..upperbound]
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

// modular multiplication to numbers up to 10^18 in O(1)
// __int128 is a well accepted gcc extension also compatible with clang
inline ull mul(ull a, ull b, ull c) { return __int128(a) * b % c; }

// modular exponatiation in O(log(n))
inline ull power(ull a, ull b, ull c) {
  ull res = 1;
  while (b > 0) {
    if (b & 1) res = mul(res, a, c);
    a = mul(a, a, c);
    b /= 2;
  }
  return res;
}

// miller-rabin strong pseudoprimality test in complexity O(log(n))
// returns false if n is composite
// returns true if n is prime or strong pseudoprime in base a
bool witness(ull n, ull d, ull s, ull a) {
  ull x = power(a, d, n), y;

  // pass through all a^(d*2^k) mod n ( 0 <= k <= s )
  while (s--) {
    y = mul(x, x, n);
    // if y is equal to 1 it must have been a square of -1 or 1 mod n to be prime
    // if not the number is composite
    if (y == 1 and x != 1 and x != n - 1) return false;
    x = y;
  }
  // if a^(d*2^s) != 1 mod n than n is not prime
  // a^(n-1) = 1 mod n for every n prime (fermats little theorem)
  if (y != 1) return false;
  // if the number is not confirmed composite return that it is either a prime
  // or strong pseudoprime in base a
  return true;
}

// all numbers up to 10^18 are confirmed composite if these bases are used
// if numbers are up to 10^9 use primes_small to confirm compositeness
ull primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
ull primes_small[] = {2, 3, 5, 7, 11};

// ckeck primality up to 10^18 in O(log(n)*k)
// to numbers up to 10^18, testing all 9 prime numbers smaller or equal to 23 suffices
bool is_prime_miller_rabin(ull n) {
  // trivial cases
  if (n == 2 or n == 3) return true;
  if (n < 2 or n % 2 == 0 or n % 3 == 0) return false;

  // calculate d = biggest odd number divisor of n-1
  // s = number of the biggest power of two that divides n-1
  // such that n-1 = d*2^s (d odd)
  // __builtin_ctzll returns expoent of biggest power of two that divides n-1
  ull s = __builtin_ctzll(n - 1);
  ull d = (n - 1) >> s;

  // check primality with the 13 bases
  for (ull p : primes) {
    if (p == n) return true;
    if (!witness(n, d, s, p)) return false;  // if composite returns false
  }
  // after the iterations all remaining numbers are prime
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve(10000000);
  int q; cin >> q;
  while (q--) {
    ll x; cin >> x;
    bool can = false;
    for (int prime : p) {
      if (is_prime_miller_rabin(x + prime)) {
        can = true;
        cout << prime << '\n';
        break;
      }
    }
    if (!can) cout << -1 << '\n';
  }
}
