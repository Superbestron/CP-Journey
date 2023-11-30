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

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x - p2.x, p1.y - p2.y);
}               // return double

// A function to calculate the absolute area of a triangle
double absArea(point p, point q, point r) {
  return abs((p.x * q.y + q.x * r.y + r.x * p.y) - (p.y * q.x + q.y * r.x + r.y * p.x));
}

struct vec {
  double x, y;  // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {}
  vec(point p1, point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}
};

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return {b.x - a.x, b.y - a.y};
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

double cal_tri_area(point a, point b, point c) {
  return fabs(cross(vec(a, b), vec(a, c)) / 2.0);
}

// Rotating Caliper Algorithm to Get All AntiPodal Points
// Here P has no repeated vertex at the back
vector<pair<int, int>> GetAllAntiPodalPairs(vector<point> &P) {
  int n = P.size();

  if (n == 1) return {};
  if (n == 2) return {{0, 1}};

  vector<pair<int, int>> ans;
  int i0 = n - 1;
  int i = 0;
  int j = i + 1;
  int j0 = j;
  while (cal_tri_area(P[i], P[i + 1], P[j + 1]) > cal_tri_area(P[i], P[i + 1], P[j])) {
    j = j + 1;
    j0 = j;
  }
  ans.emplace_back(i, j);
  while (j != i0) {
    i = i + 1;
    ans.emplace_back(i, j);

    while (cal_tri_area(P[i], P[i + 1], P[j + 1]) > cal_tri_area(P[i], P[i + 1], P[j])) {
      j = j + 1;
      if ((i != j0 && j != i0))
        ans.emplace_back(i, j);
      else
        return ans;
    }
    if (cal_tri_area(P[j], P[i + 1], P[j + 1]) == cal_tri_area(P[i], P[i + 1], P[j])) {
      if (i != j0 && j != i0)
        ans.emplace_back(i, j + 1);
      else
        ans.emplace_back(i + 1, j);
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int C;
  cin >> C;
  vector<point> P;
  for (int i = 0; i < C; i++) {
    int x, y;
    cin >> x >> y;
    P.emplace_back(x, y);
  }
  vector<point> hull = CH_Andrew(P);
  if (hull.size() == 1) {
    cout << "0" << endl;
    return 0;
  }
  hull.pop_back();
  auto pairs = GetAllAntiPodalPairs(hull);
  double max_dist = 0.0;
  for (auto p : pairs) {
    max_dist = max(max_dist, dist(hull[p.first], hull[p.second]));
  }
  cout << fixed << setprecision(6) << max_dist << endl;
}
