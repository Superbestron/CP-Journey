#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll MOD = 1e9;
const int MAX_N = 2;                             // 2x2 for Fib matrix
struct Matrix { ll mat[MAX_N][MAX_N]; };         // we return a 2D array

ll mod(ll a, ll m) { return ((a % m) + m) % m; }     // ensure positive answer

Matrix matMul(Matrix a, Matrix b) {              // normally O(n^3)
  Matrix ans;                                    // but O(1) as n = 2
  for (auto & i : ans.mat)
    for (long long & j : i)
      j = 0;
  for (int i = 0; i < MAX_N; ++i)
    for (int k = 0; k < MAX_N; ++k) {
      if (a.mat[i][k] == 0) continue;            // optimization
      for (int j = 0; j < MAX_N; ++j) {
        ans.mat[i][j] += mod(a.mat[i][k], MOD) * mod(b.mat[k][j], MOD);
        ans.mat[i][j] = mod(ans.mat[i][j], MOD); // modular arithmetic
      }
    }
  return ans;
}

Matrix matPow(Matrix base, ll p) {              // normally O(n^3 log p)
  Matrix ans;                                    // but O(log p) as n = 2
  for (int i = 0; i < MAX_N; ++i)
    for (int j = 0; j < MAX_N; ++j)
      ans.mat[i][j] = (i == j);                  // prepare identity matrix
  while (p) {                                    // iterative D&C version
    if (p & 1)                                     // check if p is odd
      ans = matMul(ans, base);                   // update ans
    base = matMul(base, base);                   // square the base
    p >>= 1;                                     // divide p by 2
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll P, K, Y;
  cin >> P;
  Matrix ans;                                  // Fibonaccci matrix
  ans.mat[0][0] = 1;
  ans.mat[0][1] = 1;
  ans.mat[1][0] = 1;
  ans.mat[1][1] = 0;
  for (int i = 0; i < P; i++) {
    cin >> K >> Y;
    Matrix result = matPow(ans, Y);                        // O(log n)
    printf("%d %lld\n", K, result.mat[0][1]);             // this if fib(n) % MOD
  }
}
