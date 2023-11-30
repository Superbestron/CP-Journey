#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll MOD;
const int MAX_N = 41;                             // 2x2 for Fib matrix
struct Matrix { ll mat[MAX_N][MAX_N]; };         // we return a 2D array

ll mod(ll a, ll m) { return ((a % m) + m) % m; }     // ensure positive answer

Matrix matMul(Matrix a, Matrix b, int r, int c1, int c2) {              // normally O(n^3)
  Matrix ans;                                    // but O(1) as n = 2
  for (auto &i : ans.mat)
    for (ll &j : i)
      j = 0;
  for (int i = 0; i < r; ++i)
    for (int k = 0; k < c1; ++k) {
      if (a.mat[i][k] == 0) continue;            // optimization
      for (int j = 0; j < c2; ++j) {
        ans.mat[i][j] += mod(a.mat[i][k], MOD) * mod(b.mat[k][j], MOD);
        ans.mat[i][j] = mod(ans.mat[i][j], MOD); // modular arithmetic
      }
    }
  return ans;
}

Matrix matPow(Matrix base, int r, ll p) {              // normally O(n^3 log p)
  Matrix ans;                                    // but O(log p) as n = 2
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < r; ++j)
      ans.mat[i][j] = (i == j);                  // prepare identity matrix
  while (p) {                                    // iterative D&C version
    if (p & 1)                                     // check if p is odd
      ans = matMul(ans, base, r, r, r);                   // update ans
    base = matMul(base, base, r, r, r);                   // square the base
    p >>= 1;                                     // divide p by 2
  }
  return ans;
}

int main() {
  ll Q, T, n;
  cin >> n;
  vector<ll> x(n);
  vector<ll> a(n + 1);
  for (ll &i : a) cin >> i;
  for (ll &i : x) cin >> i;
  Matrix ori;
  for (auto &i : ori.mat)
    for (ll &j : i)
      j = 0;
  for (int i = 0; i <= n; i++) {
    ori.mat[1][i] = a[i];
  }
  ori.mat[0][0] = 1;
  for (int i = 2; i <= n; i++) {
    ori.mat[i][i - 1] = 1;
  }
  cin >> Q;
  while (Q--) {
    cin >> T >> MOD;
    if (T < n) {
      cout << x[T] % MOD << '\n';
      continue;
    }
    Matrix ans = matPow(ori, n + 1, T - (n - 1));                        // O(log n)
    Matrix multi;
    for (int i = 0; i < n; i++) multi.mat[n - i][0] = x[i];
    multi.mat[0][0] = 1;
    Matrix res = matMul(ans, multi, n + 1, n + 1, 1);
    cout << res.mat[1][0] << '\n';
  }
}
