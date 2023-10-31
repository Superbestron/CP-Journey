#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;
typedef long double ld;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> v(n);
    ll ans = 0;
    for (int &i : v) cin >> i;
    set<int> left;
    map<int, int> right;
    for (int i = n - 1; i >= 0; i--) {
      if (right.count(v[i])) continue;
      right[v[i]] = i;
    }
    for (int i = 0; i < n; i++) {
      if (!left.count(v[i])) {
        left.insert(v[i]);
        ans += right.size();
      }
      if (right.count(v[i]) && right[v[i]] == i) right.erase(v[i]);
    }
    cout << ans << '\n';
  }
}