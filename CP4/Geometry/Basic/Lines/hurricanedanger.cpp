#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

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

struct vec {
  double x, y; // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(const point &a, const point &b) {      // convert 2 points
  return {b.x - a.x, b.y - a.y};                  // to vector a->b
}

vec scale(const vec &v, double s) {              // s = [<1..1..>1]
  return {v.x * s, v.y * s};                      // shorter/eq/longer
}

point translate(const point &p, const vec &v) {  // translate p
  return {p.x + v.x, p.y + v.y};                // according to v
}

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x - p2.x, p1.y - p2.y);            // return double
}

// returns the dot product of two vectors a and b
double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

// returns the squared value of the normalized vector
double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

double distToLine(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  // formula: c = a + u*ab
  c = translate(a, scale(ab, u));                // translate a to c
  return dist(p, c);                             // Euclidean distance
}

int main() {
  int n, x1, y1, x2, y2, m, x, y;
  string s;
  cin >> n;
  while (n--) {
    cin >> x1 >> y1 >> x2 >> y2 >> m;
    point one(x1, y1);
    point two(x2, y2);
    point temp;
    double min_dist = 1e9;
    vector<string> cities;
    while (m--) {
      cin >> s >> x >> y;
      point curr(x, y);
      double dist = distToLine(curr, one, two, temp);
      if (min_dist - dist > EPS) {
        min_dist = dist;
        cities.clear();
        cities.push_back(std::move(s));
      } else if (fabs(dist - min_dist) < EPS) cities.push_back(std::move(s));
    }
    for (auto &city : cities) cout << city << ' ';
    cout << '\n';
  }
}
