#include <bits/stdc++.h>
using namespace std;

int mod(int a, int m) {                          // returns a (mod m)
  return ((a % m) + m) % m;                        // ensure positive answer
}

int modPow(int b, int p, int m) {                // assume 0 <= b < m
  if (p == 0) return 1;
  int ans = modPow(b, p / 2, m);                   // this is O(log p)
  ans = mod(ans * ans, m);                         // double it first
  if (p & 1) ans = mod(ans * b, m);                  // *b if p is odd
  return ans;                                    // ans always in [0..m-1]
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int c, x, y, n; cin >> c;
  while (c--) {
    cin >> x >> y >> n;
    cout << modPow(x, y, n) << '\n';
  }
}
