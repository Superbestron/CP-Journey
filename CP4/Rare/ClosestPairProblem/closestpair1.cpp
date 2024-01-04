#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
int n;

struct point {
  double x, y;                                   // if need more precision
  point() { x = y = 0.0; }                       // default constructor
  point(double _x, double _y) : x(_x), y(_y) {}  // constructor
  bool operator<(point other) const {          // override < operator
    if (fabs(x - other.x) > EPS)                   // useful for sorting
      return x < other.x;                        // by x-coordinate
    return y < other.y;                          // if tie, by y-coordinate
  }
  // use EPS (1e-9) when testing equality of two floating points
  bool operator==(point other) const {
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
  }
};

vector<point> P;

pair<point, point> closest_pair() {
  sort(P.begin(), P.end());
  set<point> s;
  pair<point, point> ans;

  double best_dist = 1e18;
  for (int i = 0, j = 0; i < n; ++i) {
    double d = best_dist;
    while (fabs(P[i].x - P[j].x) - d > EPS) {
      s.erase({P[j].y, P[j].x});
      j++;
    }

    auto it1 = s.lower_bound({P[i].y - d, P[i].x});
    auto it2 = s.upper_bound({P[i].y + d, P[i].x});

    for (auto it = it1; it != it2; ++it) {
      double dx = P[i].x - it->y;
      double dy = P[i].y - it->x;
      double dist = hypot(dx, dy);
      if (best_dist > dist) {
        best_dist = dist;
        ans = {point(it->y, it->x), P[i]};
      }
    }
    s.emplace(P[i].y, P[i].x);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  long double x, y;
  while (cin >> n) {
    if (n == 0) break;
    P.clear();
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      P.emplace_back(x, y);
    }
    auto [p1, p2] = closest_pair();
    cout << setprecision(2) << fixed << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << '\n';
  }
}
