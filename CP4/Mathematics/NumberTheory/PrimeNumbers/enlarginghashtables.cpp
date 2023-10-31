#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

void sieve(ll upperbound) { // range = [0..upperbound]
  sieve_size = upperbound+1; // to include upperbound
  bs.set(); // all 1s
  bs[0] = bs[1] = 0; // except index 0+1
  for (ll i = 2; i < sieve_size; ++i) if (bs[i]) {
// cross out multiples of i starting from i*i
      for (ll j = i*i; j < sieve_size; j += i) bs[j] = 0;
      p.push_back(i); // add prime i to the list
    }
}

bool isPrime(ll N) { // good enough prime test.txt
  if (N < sieve_size) return bs[N]; // O(1) for small primes
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i)
    if (N % p[i] == 0)
      return false;
  return true; // slow if N = large
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  sieve(100000);
  int n;
  while (cin >> n && n != 0) {
    int mini = 2 * n;
    while (!isPrime(mini)) mini++;
    cout << mini;
    if (!isPrime(n)) cout << " (" << n << " is not prime)";
    cout << '\n';
  }
}