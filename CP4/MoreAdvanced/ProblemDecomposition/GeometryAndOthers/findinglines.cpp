#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

/*
 * My first randomisation algorithmic problem. Notice that if we pick a random line between 2 points, the probability
 * of picking a line that is correct is 0.2 ^ 2 = 0.04. Thus probability of no false negative is (1 - 0.04 ^ k) and
 * if we set k = 200, this is practically 1.
 */

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

// returns the cross product of two vectors a and b
double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, p;
  double x, y;
  cin >> n >> p;
  if (n == 1) {
    cout << "possible\n";
    return 0;
  }
  vector<point> v;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    v.emplace_back(x, y);
  }
  for (int i = 0; i < 200; i++) {
    point a = v[rand() % n];
    point b = v[rand() % n];
    while (b == a) b = v[rand() % n];
    int cnt = 2;
    for (int j = 0; j < n; j++) {
      if (v[j] == a || v[j] == b) continue;
      if (collinear(a, b, v[j])) cnt++;
    }
    if (100.0 * cnt / n >= p) {
      cout << "possible\n";
      return 0;
    }
  }
  cout << "impossible\n";
}
