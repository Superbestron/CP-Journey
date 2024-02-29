#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<ll, ll> ii;
const double EPS = 1e-9;

vector<double> a;
int T, N, F;

bool can(double x) {
  int cnt = 0;
  for (int i = 0; i < N; i++) {
    cnt += floor(a[i] / x);
  }
  return cnt >= F + 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> N >> F;
    a.assign(N, 0);
    double max_V = 0;
    for (double &i : a) {
      cin >> i;
      i = i * i * M_PI;
      max_V = max(max_V, i);
    }
    double lo = 0, hi = max_V;
    for (int i = 0; i < 50; ++i) {
      double mid = (lo + hi) / 2.0;
      can(mid) ? lo = mid : hi = mid;
    }
    cout << setprecision(3) << fixed << lo << '\n';
  }
}
