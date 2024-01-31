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

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, x, y, tc = 1;
  while (cin >> n && n != 0) {
    vector<point> P;
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      P.emplace_back(x, y);
    }
    P.push_back(P[0]);

    vector<point> left = P;
    for (int i = 1; i < P.size(); i++) {
      left = cutPolygon(P[i], P[i - 1], left);
    }

    cout << "Floor #" << tc++ << '\n';
    cout << "Surveillance is ";
    if (left.empty()) cout << "impossible.\n\n";
    else cout << "possible.\n\n";
  }
}
