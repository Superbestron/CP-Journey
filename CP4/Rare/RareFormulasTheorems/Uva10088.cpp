#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct point {
  ll x, y;   // only used if more precision is needed
  point(ll _x, ll _y) : x(_x), y(_y) {}        // user-defined
};

// returns the area of polygon P
double area(const vector<point> &P) {
  double ans = 0.0;
  for (ll i = 0; i < (ll) P.size() - 1; ++i)      // Shoelace formula
    ans += (P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
  return fabs(ans) / 2.0;                          // only do / 2.0 here
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll N, x, y;
  while (cin >> N) {
    if (N == 0) break;
    vector<point> P;
    ll integer_points = 0;
    for (ll i = 0; i < N; i++) {
      cin >> x >> y;
      P.emplace_back(x, y);
    }
    P.push_back(P[0]);
    for (ll i = 0; i < N; i++) {
      integer_points += gcd(abs(P[i + 1].x - P[i].x), abs(P[i + 1].y - P[i].y));
    }
    ll A = area(P);
    cout << A - integer_points / 2 + 1 << '\n';
  }
}
