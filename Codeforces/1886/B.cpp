#include <bits/stdc++.h>
using namespace std;

int t, px, py, ax, ay, bx, by;

inline bool in_circle(int x, int y, int cx, int cy, double r) {
  return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r;
}

inline bool intersect(int x1, int y1, int x2, int y2, double r1, double r2) {
  double d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
  return d <= (r1 + r2) * (r1 + r2);
}

bool can(double w) {
  bool home_covered_in1 = in_circle(0, 0, ax, ay, w), house_covered_in1 = in_circle(px, py, ax, ay, w);
  bool home_covered_in2 = in_circle(0, 0, bx, by, w), house_covered_in2 = in_circle(px, py, bx, by, w);
  bool both_in_circle_1 = home_covered_in1 && house_covered_in1;
  bool both_in_circle_2 = home_covered_in2 && house_covered_in2;
  bool both_covered = (home_covered_in1 || home_covered_in2) && (house_covered_in1 || house_covered_in2);
  return both_in_circle_1 || both_in_circle_2 || (intersect(ax, ay, bx, by, w, w) && both_covered);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> px >> py >> ax >> ay >> bx >> by;
    double lo = 0, hi = 4000.0;
    for (int i = 0; i < 50; ++i) {
        double mid = (lo + hi) / 2.0;
        can(mid) ? hi = mid : lo = mid;
    }
    cout << fixed << setprecision(6) << hi << '\n';
  }
}