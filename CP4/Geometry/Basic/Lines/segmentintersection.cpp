#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;

const double EPS = 1e-9;

struct point {
  double x, y;                                   // only used if more precision is needed
  point() { x = y = 0.0; }                       // default constructor
  point(double _x, double _y) : x(_x), y(_y) {}  // user-defined
  bool operator==(point other) const {
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
  }
  bool operator<(const point &p) const {
    return x < p.x || (abs(x - p.x) < EPS && y < p.y);
  }
  point operator-(const point &p) const {
    return {x - p.x, y - p.y};
  }
  point operator*(double s) const { return {s * x, s * y}; }
  point operator/(double s) const { return {x / s, y / s}; }
  double operator^(point p) const { return x * p.y - y * p.x; }
  double operator*(point p) const { return x * p.x + y * p.y; }
  friend std::ostream& operator<<(std::ostream& os, const point& p) {
    os << p.x << ' ' << p.y;
    return os;
  }
};

void lineSegmentIntersection(point p1, point p2, point p3, point p4) {
  point s1 = p2 - p1, s2 = p4 - p3;
  double a = s1 ^ s2, a1 = s1 ^ (p3 - p1), a2 = s2 ^ (p3 - p1);
  if (p1 == p2) {
    if (p3 == p4) {
      if (p1 == p3) cout << p1 << "\n";
      else cout << "none\n";
    } else
      lineSegmentIntersection(p3, p4, p1, p2);
  } else if (!(s1 ^ s2)) {
    double b1 = p1 * s1, c1 = p2 * s1, b2 = p3 * s1, c2 = p4 * s1;
    if (a1 || a2 || max(b1, min(b2, c2)) > min(c1, max(b2, c2)))
      cout << "none\n";
    else {
      point r1 = min(b2, c2) < b1 ? p1 : (b2 < c2 ? p3 : p4),
          r2 = max(b2, c2) > c1 ? p2 : (b2 > c2 ? p3 : p4);
      if (r1 == r2) cout << r1 << "\n";
      else cout << min(r1, r2) << " " << max(r1, r2) << "\n";
    }
  } else {
    if (a < 0) a = -a, a1 = -a1, a2 = -a2;
    if (a1 > 0 || a < -a1 || a2 > 0 || a < -a2) cout << "none\n";
    else cout << p1 - s1 * a2 / a << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, x1, y1, x2, y2, x3, y3, x4, y4;
  cin >> n;
  cout << fixed << setprecision(2);
  for (int i = 0; i < n; i++) {
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    point p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4);
    lineSegmentIntersection(p1, p2, p3, p4);
  }
}
