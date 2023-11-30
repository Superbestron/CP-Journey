#include <bits/stdc++.h>
using namespace std;

const int N = 1e4;
const double EPS = 1e-9;
int case_counter = 0, degree;
vector<double> poly;
vector<int> coefficients;

double fsquared(double x) {
  double t = 0, cur = 1;
  for (double i : poly) {
    t += i * cur;
    cur *= x;
  }
  return t * t;
}

double cal_vol(double x_lo, double x_hi) { // volume of revolution
  double dx = (x_hi - x_lo) / ((double) N);  // N + 1 = nt
  double sum = 0;
  for (int i = 0; i <= N; i++) {
    double x = x_lo + i * dx;
    sum += coefficients[i] * fsquared(x);
  }
  return M_PI * sum * dx / 3.0;
}

int main() {
  cout << fixed << setprecision(2);
  // Generate Simpson's Rule Coefficients
  coefficients.emplace_back(1);
  for (int i = 1; i < N; i++) coefficients.emplace_back((i % 2) ? 4 : 2);
  coefficients.emplace_back(1);

  while (cin >> degree) {
    poly.assign(degree + 1, 0);
    for (int i = 0; i <= degree; i++) cin >> poly[i];
    double x_lo, x_hi, difference, target = 0;
    cin >> x_lo >> x_hi >> difference;
    cout << "Case " << ++case_counter << ": " << cal_vol(x_lo, x_hi) << '\n';

    for (int i = 0; i < 8; i++) {
      target += difference;
      double lo = x_lo, hi = x_hi + 10;
      while (fabs(hi - lo) > EPS) {
        double mid = (lo + hi) / 2;
        if (cal_vol(x_lo, mid) > target) hi = mid;
        else lo = mid;
      }
      if (lo > x_hi) {
        if (i == 0) cout << "insufficient volume";
        break;
      } else {
        if (i != 0) cout << " " << lo - x_lo;
        else cout << lo - x_lo;
      }
    }
    cout << '\n';
  }
}
