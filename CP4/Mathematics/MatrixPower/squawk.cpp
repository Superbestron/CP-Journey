#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 100;                             // 2x2 for Fib matrix
int n;
struct Matrix { ll mat[MAX_N][MAX_N]; };         // we return a 2D array

Matrix matMul(Matrix a, Matrix b) {              // normally O(n^3)
  Matrix ans;                                    // but O(1) as n = 2
  for (auto & i : ans.mat)
    for (long long & j : i)
      j = 0;
  for (int i = 0; i < n; ++i)
    for (int k = 0; k < n; ++k) {
      if (a.mat[i][k] == 0) continue;            // optimization
      for (int j = 0; j < n; ++j) {
        ans.mat[i][j] += a.mat[i][k] * b.mat[k][j];
      }
    }
  return ans;
}

Matrix matPow(Matrix base, ll p) {              // normally O(n^3 log p)
  Matrix ans;                                    // but O(log p) as n = 2
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
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
  ll m, s, t, x, y, sum = 0;
  cin >> n >> m >> s >> t;
  Matrix ans;                                  // Fibonaccci matrix
  for (auto & i : ans.mat)
    for (long long & j : i)
      j = 0;
  for (int i = 0; i < m; i++) {
    cin >> x >> y;
    ans.mat[x][y] = 1;
    ans.mat[y][x] = 1;
  }
  Matrix result = matPow(ans, t);                        // O(log n)
  for (int i = 0; i < n; i++) {
    sum += result.mat[s][i];
  }
  cout << sum << '\n';
}
