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

// compute the intersection point between line segment p-q and line A-B
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y - A.y, b = A.x - B.x, c = B.x * A.y - A.x * B.y;
  double u = fabs(a * p.x + b * p.y + c);
  double v = fabs(a * q.x + b * q.y + c);
  return {(p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v)};
}

// cuts polygon Q along the line formed by point A->point B (order matters)
// (note: the last point must be the same as the first point)
vector<point> cutPolygon(point A, point B, const vector<point> &Q) {
  vector<point> P;
  for (int i = 0; i < (int) Q.size(); ++i) {
    double left1 = cross(toVec(A, B), toVec(A, Q[i])), left2 = 0;
    if (i != (int) Q.size() - 1) left2 = cross(toVec(A, B), toVec(A, Q[i + 1]));
    if (left1 > -EPS) P.push_back(Q[i]);         // Q[i] is on the left
    if (left1 * left2 < -EPS)                      // crosses line AB
      P.push_back(lineIntersectSeg(Q[i], Q[i + 1], A, B));
  }
  if (!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front());                      // wrap around
  return P;
}

pair<double, int> cal_smallest_angle(const vector<point> &P) {
  // find most pointy edge
  double mx = angle(P[P.size() - 2], P[0], P[1]);
  int idx = 0;
  for (int i = 0; i < P.size() - 2; i++) {
    double curr = angle(P[i], P[i + 1], P[i + 2]);
    if (curr < mx) {
      mx = curr;
      idx = i + 1;
    }
  }
  return {mx, idx};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, x, y;
  while (cin >> n && n != 0) {
    vector<point> P;
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      P.emplace_back(x, y);
    }
    P.push_back(P[0]);
    while (P.size() > 4) {
      vector<point> new_polygon;
      auto [smallest_angle, idx] = cal_smallest_angle(P);
      for (int i = 0; i < P.size() - 1; i++) {
        if (idx == i) continue;
        new_polygon.push_back(P[i]);
      }
      new_polygon.push_back(new_polygon[0]);
      // check if angles are worse off
      auto [new_smallest_angle, new_idx] = cal_smallest_angle(new_polygon);
      if (smallest_angle - new_smallest_angle > EPS) break;
      P = new_polygon;
    }
    cout << P.size() - 1 << ' ';
    for (int i = 0; i < P.size() - 1; i++) cout << P[i].x << ' ' << P[i].y << ' ';
    cout << '\n';
  }
}
