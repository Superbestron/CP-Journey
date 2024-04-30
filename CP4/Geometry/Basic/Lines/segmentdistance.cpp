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

bool lineSegmentIntersection(point p1, point p2, point p3, point p4) {
  point s1 = p2 - p1, s2 = p4 - p3;
  double a = s1 ^ s2, a1 = s1 ^ (p3 - p1), a2 = s2 ^ (p3 - p1);
  if (p1 == p2) {
    if (p3 == p4) return p1 == p3;
    else return lineSegmentIntersection(p3, p4, p1, p2);
  } else if (!(s1 ^ s2)) {
    double b1 = p1 * s1, c1 = p2 * s1, b2 = p3 * s1, c2 = p4 * s1;
    return (!(a1 || a2 || max(b1, min(b2, c2)) > min(c1, max(b2, c2))));
  } else {
    if (a < 0) a = -a, a1 = -a1, a2 = -a2;
    return (!(a1 > 0 || a < -a1 || a2 > 0 || a < -a2));
  }
}

struct vec {
  double x, y; // name: 'vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(const point &a, const point &b) {      // convert 2 points
  return {b.x - a.x, b.y - a.y};                  // to vector a->b
}

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x - p2.x, p1.y - p2.y);            // return double
}

// returns the dot product of two vectors a and b
double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

// returns the squared value of the normalized vector
double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

point translate(const point &p, const vec &v) {  // translate p
  return {p.x + v.x, p.y + v.y};                // according to v
}

vec scale(const vec &v, double s) {              // s = [<1..1..>1]
  return {v.x * s, v.y * s};                      // shorter/eq/longer
}

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double temp = norm_sq(ab);
  if (temp == 0) {
    c = a;
    return dist(p, a);
  }
  double u = dot(ap, ab) / temp;
  // formula: c = a + u*ab
  c = translate(a, scale(ab, u));                // translate a to c
  return dist(p, c);                             // Euclidean distance
}

// returns the distance from p to the line segment ab defined by
// two points a and b (technically, a has to be different than b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  if (u < 0.0) {                                 // closer to a
    c = point(a.x, a.y);
    return dist(p, a);                           // dist p to a
  }
  if (u > 1.0) {                                 // closer to b
    c = point(b.x, b.y);
    return dist(p, b);                           // dist p to b
  }
  return distToLine(p, a, b, c);                 // use distToLine
}

double distFromTwoLineSegment(point &a1, point &a2, point &b1, point &b2) {
  if (lineSegmentIntersection(a1, a2, b1, b2)) return 0;
  else {
    point c;
    return min({distToLineSegment(a1, b1, b2, c), distToLineSegment(a2, b1, b2, c),
                 distToLineSegment(b1, a1, a2, c), distToLineSegment(b2, a1, a2, c)});
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
    cout << distFromTwoLineSegment(p1, p2, p3, p4) << '\n';
  }
}
