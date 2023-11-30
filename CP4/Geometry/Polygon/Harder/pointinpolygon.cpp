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

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x - p2.x, p1.y - p2.y);
}               // return double

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

// returns 1/0/-1 if point p is inside/on (vertex/edge)/outside of
// either convex/concave polygon P
int insidePolygon(point pt, const vector<point> &P) {
  int n = (int) P.size();
  if (n <= 3) return -1;                         // avoid point or line
  bool on_polygon = false;
  for (int i = 0; i < n - 1; ++i)                  // on vertex/edge?
    if (fabs(dist(P[i], pt) + dist(pt, P[i + 1]) - dist(P[i], P[i + 1])) < EPS)
      on_polygon = true;
  if (on_polygon) return 0;                      // pt is on polygon
  double sum = 0.0;                              // first = last point
  for (int i = 0; i < n - 1; ++i) {
    if (ccw(pt, P[i], P[i + 1]))
      sum += angle(P[i], pt, P[i + 1]);            // left turn/ccw
    else
      sum -= angle(P[i], pt, P[i + 1]);            // right turn/cw
  }
  return fabs(sum) > M_PI ? 1 : -1;              // 360d->in, 0d->out
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, x, y;
  while (cin >> n && n != 0) {
    vector<point> P;
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      P.emplace_back(x, y);
    }
    P.push_back(P[0]);
    cin >> m;
    for (int i = 0; i < m; i++) {
      cin >> x >> y;
      int ans = insidePolygon(point(x, y), P);
      if (ans == 1) cout << "in\n";
      else if (ans == 0) cout << "on\n";
      else cout << "out\n";
    }
  }
}
