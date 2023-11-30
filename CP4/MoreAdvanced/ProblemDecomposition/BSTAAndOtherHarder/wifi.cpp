#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const double EPS = 1e-9;
int T, N, M;
vector<int> v;

bool can(double x) {
  double covered = -1e9;
  int used = 0;
  for (int i = 0; i < M; i++) {
    if (fabs(v[i] - covered) - x > EPS) {
      used++;
      covered = v[i] + x;
    }
  }
  return used <= N;
}

int main() {
  cin >> T;
  while (T--) {
    cin >> N >> M;
    v.assign(M, 0);
    for (int &i : v) cin >> i;
    sort(v.begin(), v.end());
    double lo = 0, hi = 1000000;
    while (fabs(hi - lo) > EPS) {
      double mid = (lo + hi) / 2.0;
      can(mid) ? hi = mid : lo = mid;
    }
    cout << setprecision(1) << fixed << round(lo * 10) / 10 << '\n';
  }
}
