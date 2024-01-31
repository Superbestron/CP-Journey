#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
const int MAX_N = 70;                             // adjust as needed
struct AugmentedMatrix { double mat[MAX_N][MAX_N + 1]; };
struct ColumnVector { double vec[MAX_N]; };

// Replace whatever operations in the gaussian elimination with modulo operations.

int N, p;

int mod(int a, int n) {
  return (a % n + n) % n;
}

int extEuclid(int a, int b, int &x, int &y) {  // pass x and y by ref
  int xx = y = 0;
  int yy = x = 1;
  while (b) {  // repeats until b == 0
    int q = a / b;
    tie(a, b) = tuple(b, a % b);
    tie(x, xx) = tuple(xx, x - q * xx);
    tie(y, yy) = tuple(yy, y - q * yy);
  }
  return a;  // returns gcd(a, b)
}

int modInverse(int a, int n) {  // returns modular inverse of a mod n
  int x, y;
  extEuclid(a, n, x, y);
  return mod(x, n);
}

ColumnVector GaussianElimination(int N, AugmentedMatrix Aug) {
  // input: N, Augmented Matrix Aug, output: Column vector X, the answer
  for (int i = 0; i < N - 1; ++i) {                // forward elimination
    int l = i;
    for (int j = i + 1; j < N; ++j)                // row with max col value
      if (fabs(Aug.mat[j][i]) > fabs(Aug.mat[l][i]))
        l = j;                                   // remember this row l
    // swap this pivot row, reason: minimize floating point error
    for (int k = i; k <= N; ++k)
      swap(Aug.mat[i][k], Aug.mat[l][k]);
    for (int j = i + 1; j < N; ++j)                // actual fwd elimination
      for (int k = N; k >= i; --k) {
        Aug.mat[j][k] -= mod(mod(Aug.mat[i][k] * Aug.mat[j][i], p) * modInverse(Aug.mat[i][i], p), p);
        Aug.mat[j][k] = mod(Aug.mat[j][k], p);
      }
  }

  ColumnVector Ans;                              // back substitution phase
  for (int j = N - 1; j >= 0; --j) {               // start from back
    double t = 0.0;
    for (int k = j + 1; k < N; ++k) {
      t += mod(Aug.mat[j][k] * Ans.vec[k], p);
      t = mod(t, p);
    }
    Ans.vec[j] = mod((Aug.mat[j][N] - t) * modInverse(Aug.mat[j][j], p), p); // the answer is here
  }
  return Ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  string s;
  while (N--) {
    cin >> p >> s;
    AugmentedMatrix Aug;
    int n = s.size();
    vi f(n + 1);
    for (int i = 0; i< n; i++) {
      if (s[i] == '*') f[i] = 0;
      else f[i] = (s[i] - 'a') + 1;
    }

    for (int i = 0; i < n; i++) {
      Aug.mat[i][0] = 1;
      for (int j = 1; j < n; j++) {
        Aug.mat[i][j] = mod(Aug.mat[i][j - 1] * (i + 1), p);
      }
      Aug.mat[i][n] = f[i];
    }

    ColumnVector X = GaussianElimination(n, Aug);
    for (int i = 0; i < n; i++) cout << X.vec[i] << ' ';
    cout << '\n';
  }
}
