#include <bits/stdc++.h>
using namespace std;

const int N = 1e4;
const double EPS = 1e-9;
vector<double> poly;
vector<int> coefficients;

double gcDist(double pLa, double pLo, double qLa, double qLo, double r) {
  pLa *= M_PI / 180;
  pLo *= M_PI / 180;           // degree to radian
  qLa *= M_PI / 180;
  qLo *= M_PI / 180;
  return r * acos(cos(pLa) * cos(pLo) * cos(qLa) * cos(qLo) +
      cos(pLa) * sin(pLo) * cos(qLa) * sin(qLo) + sin(pLa) * sin(qLa));
}

double EuclideanDistance(double pLa, double pLo, double qLa, double qLo, double radius) {  // 3D version
  double phi1 = (90 - pLa) * M_PI / 180;
  double theta1 = (360 - pLo) * M_PI / 180;
  double x1 = radius * sin(phi1) * cos(theta1);
  double y1 = radius * sin(phi1) * sin(theta1);
  double z1 = radius * cos(phi1);

  double phi2 = (90 - qLa) * M_PI / 180;
  double theta2 = (360 - qLo) * M_PI / 180;
  double x2 = radius * sin(phi2) * cos(theta2);
  double y2 = radius * sin(phi2) * sin(theta2);
  double z2 = radius * cos(phi2);

  double dx = x1 - x2, dy = y1 - y2, dz = z1 - z2;
  return sqrt(dx * dx + dy * dy + dz * dz);
}

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
  // Generate Simpson's Rule Coefficients
  coefficients.emplace_back(1);
  for (int i = 1; i < N; i++) coefficients.emplace_back((i % 2) ? 4 : 2);
  coefficients.emplace_back(1);
}
