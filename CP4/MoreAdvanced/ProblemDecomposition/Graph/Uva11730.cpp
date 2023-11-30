#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int S, T, tc = 1;
  sieve(10000);
  while (cin >> S >> T) {
    if (S == 0 && T == 0) break;
    vector<int> dist(10010, 1e9);
    dist[S] = 0;
    queue<int> q;
    q.push(S);
    bool found = false;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == T) {
        found = true;
        printf("Case %d: %d\n", tc++, dist[u]);
        goto done;
      }
      vector<ll> vect(primeFactors(u));
      for (int i : vect) {
        if (i == u) continue;
        int v = u + i;
        if (v > T) continue;
        if (dist[v] != 1e9) continue;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
    done:
    if (!found) printf("Case %d: %d\n", tc++, -1);
  }
}
