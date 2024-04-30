#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef long double ld;

int n;

inline void solve() {
  cin >> n;
  vll a(n);
  ld left = 0;
  for (ll &i : a) {
    cin >> i;
  }
  vector<ld> suffix(n);
  for (int i = n - 2; i >= 0; i--) {
    suffix[i] = suffix[i + 1] / 2 + (ld) a[i + 1] / 2;
  }

  for (int i = 0; i < n; i++) {
    cout << setprecision(5) << fixed << left + a[i] + suffix[i] << ' ';
    left /= 2;
    left += (ld) a[i] / 2;
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
