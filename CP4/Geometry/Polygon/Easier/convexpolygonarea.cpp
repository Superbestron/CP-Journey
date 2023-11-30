#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;

struct point {
  double x, y;   // only used if more precision is needed
  point() { x = y = 0.0; }                      // default constructor
  point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
  bool operator==(point other) const {
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
  }
  bool operator<(const point &p) const {
    return x < p.x || (abs(x - p.x) < EPS && y < p.y);
  }
};

// returns the area of polygon P
double area(const vector<point> &P) {
  double ans = 0.0;
  for (int i = 0; i < (int) P.size() - 1; ++i)      // Shoelace formula
    ans += (P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
  return fabs(ans) / 2.0;                          // only do / 2.0 here
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, x, y;
  cin >> n;
  while (n--) {
    vector<point> P;
    cin >> m;
    for (int i = 0; i < m; i++) {
      cin >> x >> y;
      P.emplace_back(x, y);
    }
    P.push_back(P[0]);
    cout << area(P) << '\n';
  }
}
