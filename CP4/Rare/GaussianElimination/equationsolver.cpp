#include <bits/stdc++.h>
using namespace std;

// With reference from Brandon Tang

const int MAX_N = 100;                             // adjust as needed
const double EPS = 1e-9;
struct AugmentedMatrix { double mat[MAX_N][MAX_N + 1]; };
struct ColumnVector { double vec[MAX_N]; };

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
        Aug.mat[j][k] -= Aug.mat[i][k] * Aug.mat[j][i] / Aug.mat[i][i];
      }
  }

  ColumnVector Ans;                              // back substitution phase
  for (int j = N - 1; j >= 0; --j) {               // start from back
    double t = 0.0;
    for (int k = j + 1; k < N; ++k)
      t += Aug.mat[j][k] * Ans.vec[k];
    Ans.vec[j] = (Aug.mat[j][N] - t) / Aug.mat[j][j]; // the answer is here
  }
  return Ans;
}

int check(int N, AugmentedMatrix Aug) {
  bool multiple = false, inconsistent = false;
  for (int i = 0; i < N && !inconsistent; i++) {
    bool all_zero = true;
    for (int j = 0; j < N; j++) {
      if (Aug.mat[i][j] != 0) {
        all_zero = false;
        break;
      }
    }

    if (all_zero) {
      if (Aug.mat[i][N] != 0) inconsistent = true;
      else multiple = true;  // infinite no. of solutions
      continue;
    }

    for (int j = i + 1; j < N && !inconsistent; j++) {
      double factor = -1;
      bool parallel = true, valid_factor = false;

      // checking parallelism
      for (int k = 0; k < N && parallel; k++) {
        if (Aug.mat[i][k] == 0 && Aug.mat[j][k] == 0) continue;
        // once there is one zero and one non-zero, it is definitely not parallel
        if (Aug.mat[i][j] == 0 || Aug.mat[j][k] == 0) parallel = false;
        else {
          if (valid_factor) {
            if (fabs(factor - Aug.mat[i][k] / Aug.mat[j][k]) > EPS) parallel = false;
          } else {
            factor = Aug.mat[i][k] / Aug.mat[j][k];
            valid_factor = true;
          }
        }
      }

      if (!parallel) continue;
      // 2 parallel lines giving different solutions => impossible
      if (fabs(factor * Aug.mat[j][N] - Aug.mat[i][N]) > EPS) inconsistent = true;
      else multiple = true;
    }
  }

  if (inconsistent) return 2;
  else if (multiple) return 1;
  else return 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  while (cin >> n) {
    if (n == 0) break;
    AugmentedMatrix Aug;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> Aug.mat[i][j];
      }
    }
    for (int i = 0; i < n; i++) cin >> Aug.mat[i][n];

    int res = check(n, Aug);
    if (res == 2) cout << "inconsistent";
    else if (res == 1) cout << "multiple";
    else {
      ColumnVector X = GaussianElimination(n, Aug);
      for (int i = 0; i < n; i++) cout << setprecision(3) << fixed << X.vec[i] << ' ';
    }
    cout << '\n';
  }
}
