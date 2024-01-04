#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 2e9 + 11;

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, n;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> n;
    cout << "Case #" << i << ": " << modPow(n, n - 2, MOD) << '\n';
  }
}
