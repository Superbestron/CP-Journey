#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

void solve() {
  cin >> n >> k;
  vi a(n), x(n), arr(n + 1);
  for (int &i : a) cin >> i;
  for (int &i : x) cin >> i;
  for (int i = 0; i < n; i++) {
    int abs_dist = abs(x[i]);
    arr[abs_dist] += a[i];
  }
  ll bullets = 0, health_sum = 0;
  for (int i = 1; i <= n; i++) {
    bullets += k;
    health_sum += arr[i];
    if (bullets < health_sum) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
