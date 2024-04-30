#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef long double ld;

int n, val;
string s;
char st, bk;

inline void solve() {
  cin >> n >> s >> st >> val >> bk;
  // convert to A
  ld area = val;
  if (st == 'P') {
    ld r = (ld) val / M_PI / 2;
    ld l = (ld) val / 4;
    if (s[0] == 'C') area = M_PI * r * r;
    else area = l * l;
  }
  for (int i = 1; i < n; i++) {
    if (s[i - 1] == 'C') {
      area /= M_PI;
      area *= 2;
    } else {
      if (s[i] == 'C') area *= M_PI / 4;
      else area /= 2;
    }
  }
  ld ans = area;
  if (bk == 'P') {
    if (s.back() == 'C') {
      ld r = sqrt(area / M_PI);
      ans = 2 * r * M_PI;
    } else {
      ans = sqrt(area) * 4;
    }
  }
  cout << setprecision(6) << fixed << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
