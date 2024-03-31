#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll INF = 1e9;

class MCBM {
 private:
  vi match, vis;                                   // global variables
  vector<vi> AL;
  unordered_set<int> freeV;
  int V, matchings;

  int Aug(int L) {
    if (vis[L]) return 0;                          // L visited, return 0
    vis[L] = 1;
    for (auto &R : AL[L])
      if ((match[R] == -1) || Aug(match[R])) {
        match[R] = L;                              // flip status
        return 1;                                  // found 1 matching
      }
    return 0;                                      // no matching
  }
 public:
  MCBM(vector<vi> &AL, unordered_set<int> &freeV) : V(AL.size()), AL(AL), freeV(freeV) {
    match.assign(V, -1);
  }
  int get_matchings() {
    matchings = 0;
    for (auto it = freeV.begin(); it != freeV.end();) {              // O(V+E)
      vi candidates;
      int L = *it;
      for (auto &R : AL[L])
        if (match[R] == -1)
          candidates.push_back(R);
      if ((int) candidates.size() > 0) {
        ++matchings;
        it = freeV.erase(it);                            // L is matched
        int a = rand() % (int) candidates.size();     // randomize this
        match[candidates[a]] = L;
      } else it++;
    }
    for (auto &f : freeV) {                        // (in random order)
      vis.assign(V, 0);                        // reset first
      matchings += Aug(f);                              // try to match f
    }
    return matchings;
  }
};

int t, n;

ll sieve_size;
bitset<10000010> bs; // 10^7 is the rough limit
vll p; // compact list of primes

bool is_prime(int x) {
  for (int i = 2; i <= sqrt(x); i++) {
    if (x % i == 0) return false;
  }
  return true;
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

bool isPrime(ll N) { // good enough prime test.txt
  if (N < sieve_size) return bs[N]; // O(1) for small primes
  for (int i = 0; i < (int) p.size() && p[i] * p[i] <= N; ++i)
    if (N % p[i] == 0)
      return false;
  return true; // slow if N = large
}

inline void solve() {
  cin >> n;
  vi a(n);
  for (int &i: a) cin >> i;
  vector<vi> AL(n, vi(n));
  unordered_set<int> freeV;
  for (int i = 0; i < n; i++) {
    freeV.insert(i);
    bool is_i_prime = isPrime(a[i]);
    for (int j = i + 1; j < n; j++) {
      bool is_j_prime = isPrime(a[j]);
      if (is_i_prime == is_j_prime) continue;
      if (gcd(a[i], a[j]) == 1) {
        AL[i].push_back(j);
        AL[j].push_back(i);
      }
    }
  }

  MCBM mcbm(AL, freeV);
  cout << mcbm.get_matchings() / 2 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  sieve(10000000);
  while (t--) {
    solve();
  }
}
