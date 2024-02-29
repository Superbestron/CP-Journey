#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, n; cin >> t;
  while (t--) {
    cin >> n;
    vector<int> v(n), prefix1(n + 1), prefix2(n + 1);
    for (int &i : v) cin >> i;
    for (int i = 0; i < n; i++) {
      if (v[i] == 2) prefix1[i + 1] = prefix1[i] + 1;
      else prefix1[i + 1] = prefix1[i];
    }
    for (int i = n - 1; i >= 0; i--) {
      if (v[i] == 2) prefix2[i] = prefix2[i + 1] + 1;
      else prefix2[i] = prefix2[i + 1];
    }
    bool can = false;
    int i = 1;
    for (; i <= n; i++) {
      if (prefix1[i] == prefix2[i]) {
        can = true;
        break;
      }
    }
    if (can) cout << i << '\n';
    else cout << -1 << '\n';
  }
}
