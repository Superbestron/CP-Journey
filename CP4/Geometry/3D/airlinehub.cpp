#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;

double gcDist(double pLa, double pLo, double qLa, double qLo, double r) {
  pLa *= M_PI / 180;
  pLo *= M_PI / 180;           // degree to radian
  qLa *= M_PI / 180;
  qLo *= M_PI / 180;
  return r * acos(cos(pLa) * cos(pLo) * cos(qLa) * cos(qLo) +
      cos(pLa) * sin(pLo) * cos(qLa) * sin(qLo) + sin(pLa) * sin(qLa));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  double lat, lon;
  while (cin >> n) {
    vector<pair<double, double>> v;
    for (int i = 0; i < n; i++) {
      cin >> lat >> lon;
      v.emplace_back(lat, lon);
    }
    reverse(v.begin(), v.end());
    double best_dist = 1e9;
    int idx;
    for (int i = 0; i < n; i++) {
      double curr_max_dist = 0;
      auto &[lat1, lon1] = v[i];
      for (int j = 0; j < n; j++) {
        auto &[lat2, lon2] = v[j];
        curr_max_dist = max(curr_max_dist, gcDist(lat1, lon1, lat2, lon2, 100));
      }
      if (best_dist > curr_max_dist) {
        best_dist = curr_max_dist;
        idx = i;
      }
    }
    cout << setprecision(2) << fixed << v[idx].first << ' ' << v[idx].second << '\n';
  }
}
