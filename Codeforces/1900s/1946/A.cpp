#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());
  int idx = ceil(n / 2.0) - 1;
  int median = a[idx];
  int ans = 0;
  for (int i = idx; i < n; i++) {
    ans += (a[i] == median);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
