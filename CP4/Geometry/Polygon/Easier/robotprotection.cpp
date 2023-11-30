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

struct vec {
  double x, y;  // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return {b.x - a.x, b.y - a.y};
}

// returns the area of polygon P
double area(const vector<point> &P) {
  double ans = 0.0;
  for (int i = 0; i < (int) P.size() - 1; ++i)      // Shoelace formula
    ans += (P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
  return fabs(ans) / 2.0;                          // only do / 2.0 here
}

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

double angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

vector<point> CH_Andrew(vector<point> &Pts) {    // overall O(n log n)
  int n = Pts.size(), k = 0;
  vector<point> H(2 * n);
  sort(Pts.begin(), Pts.end());                  // sort the points by x/y
  for (int i = 0; i < n; ++i) {                  // build lower hull
    while ((k >= 2) && !ccw(H[k - 2], H[k - 1], Pts[i])) --k;
    H[k++] = Pts[i];
  }
  for (int i = n - 2, t = k + 1; i >= 0; --i) {       // build upper hull
    while ((k >= t) && !ccw(H[k - 2], H[k - 1], Pts[i])) --k;
    H[k++] = Pts[i];
  }
  H.resize(k);
  return H;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, x, y;
  while (cin >> n && n != 0) {
    vector<point> P;
    set<point> s;
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      if (!s.count(point(x, y))) {
        P.emplace_back(x, y);
        s.insert(point(x, y));
      }
    }
    vector<point> ans(CH_Andrew(P));
    cout << setprecision(1) << fixed << area(ans) << '\n';
  }
}
