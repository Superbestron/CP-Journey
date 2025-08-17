#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

ll lcm(int a, int b) {
  return (a / gcd(a, b)) * b;
}

inline void solve() {
  cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  ll num = a[0], sum = 0;
  for (int i = 1; i < n; i++) num = lcm(num, a[i]);
  bool can = true;
  for (int i = 0; i < n; i++) sum += num / a[i];
  for (int i = 0; i < n; i++) {
    if (num <= sum) {
      can = false;
      break;
    }
  }
  if (can) {
    for (int i = 0; i < n; i++) cout << num / a[i] << ' ';
  } else cout << -1;
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
