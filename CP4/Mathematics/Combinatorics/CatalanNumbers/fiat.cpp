#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 100010;
const int p = 1e9 + 7;                             // p is a prime > MAX_N

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

ll inv(ll a) {                                   // Fermat's little theorem
  return modPow(a, p - 2, p);                      // modPow in Section 5.8
}                                                // that runs in O(log p)

ll Cat[MAX_N];

int main() {
  int N;
  cin >> N;
  Cat[0] = 1;
  for (int n = 0; n < MAX_N - 1; ++n)              // O(MAX_N * log p)
    Cat[n + 1] = ((4 * n + 2) % p * Cat[n] % p * inv(n + 2)) % p;
  cout << Cat[N] << "\n";                   // the answer is 945729344
}