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
  map<int, int> mp;
  for (int &i : a) {
    cin >> i;
    mp[i]++;
  }
  sort(a.begin(), a.end());
  int curr = -1, lim = a[n - 1];
  for (int i = 0; i < n; i++) {
    if (a[i] >= curr + 2) {
      lim = curr; // only need check till curr
      break;
    }
    curr = a[i];
  }
  int test = 0, ans = -1;
  for (auto &[num, cnt] : mp) {
    if (num > lim) break;
    if (cnt == 1) test++;
    if (test == 2) break;
    ans = max(ans, num);
  }
  cout << ans + 1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
