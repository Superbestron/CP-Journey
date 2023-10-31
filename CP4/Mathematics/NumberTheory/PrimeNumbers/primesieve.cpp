#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vll;

int sieve_size;
bitset<100000001> bs;
vll p; // compact list of primes

void sieve(int upperbound) { // range = [0..upperbound]
  sieve_size = upperbound + 1; // to include upperbound
  bs.set(); // all 1s
  bs[0] = bs[1] = 0; // except index 0+1
  for (ll i = 2; i < sieve_size; ++i) if (bs[i]) {
// cross out multiples of i starting from i*i
      for (ll j = i*i; j < sieve_size; j += i) bs[j] = 0;
      p.push_back(i); // add prime i to the list
    }
}

bool isPrime(int N) { // good enough prime test.txt
  if (N < sieve_size) return bs[N]; // O(1) for small primes
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i)
    if (N % p[i] == 0)
      return false;
  return true; // slow if N = large
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q, x;
  cin >> n >> q;
  sieve(n);
  cout << p.size() << '\n';
  while (q--) {
    cin >> x;
    cout << (isPrime(x) ? 1 : 0) << '\n';
  }
}