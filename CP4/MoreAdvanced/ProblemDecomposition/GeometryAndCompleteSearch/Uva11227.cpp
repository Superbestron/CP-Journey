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

// returns the cross product of two vectors a and b
double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T, N;
  double X, Y;
  cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cin >> N;
    set<point> st;
    vector<point> v;
    for (int i = 0; i < N; i++) {
      cin >> X >> Y;
      if (!st.count({X, Y})) {
        st.emplace(X, Y);
        v.emplace_back(X, Y);
      }
    }
    int ans = 0;
    N = v.size();
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        int temp = 0;
        for (int k = j + 1; k < N; k++) {
          if (collinear(v[i], v[j], v[k])) temp++;
        }
        ans = max(ans, temp + 2);
      }
    }
    cout << "Data set #" << tc << " contains ";
    if (N == 1) cout << "a single gnu.\n";
    else cout << N << " gnus, out of which a maximum of " << ans << " are aligned.\n";
  }
}
