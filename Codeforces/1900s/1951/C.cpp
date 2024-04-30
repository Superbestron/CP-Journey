#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t; cin >> t;
  while (t--) {
    int n, m, k; cin >> n >> m >> k;
    vi a(n);
    for (int &i : a) cin >> i;
    sort(a.begin(), a.end());
    ll ans = 0;
    int tax = 0;
    for (int i = 0; i < n; ++i) {
      ll buy = min(m, k);
      ans += buy * (a[i] + tax);
      tax += buy;
      k -= buy;
    }
    cout << ans << '\n';
  }
}
