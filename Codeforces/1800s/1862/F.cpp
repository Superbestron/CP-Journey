#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, w, f;

void solve() {
  cin >> w >> f >> n;
  vi a(n);
  int sum = 0;
  for (int &i : a) {
    cin >> i;
    sum += i;
  }
  bitset<10000 * 100 + 1> memo;
  memo[0] = true;
  for (int i = 0; i < n; i++) {
    for (int j = sum; j >= 0; j--) {
      if (j - a[i] >= 0) memo[j] = memo[j] || memo[j - a[i]];
    }
  }
  int ans = 1e9;
  for (int i = 0; i <= sum; i++) {
    if (memo[i]) {
      ans = min(ans, max((i + (w - 1)) / w, ((sum - i) + (f - 1)) / f));
    }
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
