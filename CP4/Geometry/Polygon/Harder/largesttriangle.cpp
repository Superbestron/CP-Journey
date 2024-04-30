#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

struct point {
  ll x, y;;   // only used if more precision is needed
  point() { x = y = 0; }                      // default constructor
  point(ll _x, ll _y) : x(_x), y(_y) {}        // user-defined
  bool operator==(point other) const {
    return x == other.x && y == other.y;
  }
  bool operator<(const point &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
  friend std::ostream& operator<<(std::ostream& os, const point& p) {
    os << p.x << ' ' << p.y << '\n';
    return os;
  }
};

struct vec {
  ll x, y;  // name: `vec' is different from STL vector
  vec(ll _x, ll _y) : x(_x), y(_y) {}
  vec(point p1, point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}
};

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return {b.x - a.x, b.y - a.y};
}

ll cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the '> 0'
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
  cin >> n;
  vector<point> P;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    P.emplace_back(x, y);
  }
  vector<point> ans(CH_Andrew(P));
  ans.pop_back();
  n = ans.size();

  auto cal_tri_area = [&](int a_idx, int b_idx, int c_idx) {
    point &a = ans[a_idx % n];
    point &b = ans[b_idx % n];
    point &c = ans[c_idx % n];
    return abs(cross(vec(a, b), vec(a, c)));
  };

  ll A = 0;
  for (int a = 0; a < n; a++) {
    int b = a + 1;
    for (int k = 0; k < n - 2; k++) {
      int c = a + k + 2;
      ll area = cal_tri_area(a, b, c);
      while (b + 1 < c) {
        b++;
        ll newarea = cal_tri_area(a, b, c);
        if (newarea <= area) break;
        area = newarea;
      }
      b = max(a + 1, b - 1);
      A = max(A, area);
    }
  }
  cout << fixed << setprecision(5) << A / 2.0 << '\n';
}