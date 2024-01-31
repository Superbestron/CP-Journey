#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

bool can(int mid) {
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int lo = 0, hi = 2e9;
  // variant 1
  while (hi > lo) {
    int mid = lo + (hi - lo) / 2;
    can(mid) ? hi = mid : lo = mid + 1;
  }
  // variant 2
  while (hi > lo) {
    int mid = lo + (hi - lo + 1) / 2;
    can(mid) ? lo = mid : hi = mid - 1;
  }
//  double lo = 0, hi = 1000000;
//  while (fabs(hi - lo) > EPS) {
  for (int i = 0; i < 50; ++i) {
    double mid = (lo + hi) / 2.0;
    can(mid) ? hi = mid : lo = mid;
  }
}
