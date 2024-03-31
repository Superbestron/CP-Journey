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
  int cnt = 0, ans = 0;
  for (int &i : a) {
    cin >> i;
    if (i == 1) cnt++;
  }
  if (cnt == 1) {
    cout << 0 << '\n';
    return;
  }
  int idx1, idx2;
  for (int i = 0; i < n; i++) {
    if (a[i] == 1) {
      idx1 = i;
      break;
    }
  }
  for (int i = n - 1; i >= 0; i--) {
    if (a[i] == 1) {
      idx2 = i;
      break;
    }
  }
  for (int i = idx1 + 1; i < idx2; i++) {
    if (a[i] == 0) ans++;
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
