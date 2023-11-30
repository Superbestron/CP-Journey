#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

const int N = 1e5;
const ld EPS = 1e-9;
const ld EULER = 2.71828182845904523536;
int n, degree;
ld V;
vector<int> coefficients;

inline ld fsquared(ld a, ld b, ld x) {
  ld t = a * pow(EULER, -(x * x)) + b * pow(x, 0.5);
  return t * t;
}

ld cal_vol(ld h, ld a, ld b) { // volume of revolution
  ld dx = h / N;
  ld sum = 0;
  for (int i = 0; i <= N; i++) {
    ld x = i * dx;
    sum += coefficients[i] * fsquared(a, b, x);
  }
  return M_PI * sum * dx / 3.0;
}

int main() {
  // Generate Simpson's Rule Coefficients
  coefficients.emplace_back(1);
  for (int i = 1; i < N; i++) coefficients.emplace_back((i % 2) ? 4 : 2);
  coefficients.emplace_back(1);
  cin >> V >> n;
  ld best_fit = 1e9;
  int idx;
  for (int i = 0; i < n; i++) {
    ld ak, bk, hk;
    cin >> ak >> bk >> hk;
    ld ans = cal_vol(hk, ak, bk);
    if (best_fit - fabs(ans - V) > -EPS) {
      best_fit = fabs(ans - V);
      idx = i;
    }
  }
  cout << idx << '\n';
}
