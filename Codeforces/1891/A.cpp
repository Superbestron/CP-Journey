#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, n;
  cin >> t;
  unordered_set<int> s = {1,2,4,8,16};
  while (t--) {
    cin >> n;
    vector<int> v(n);
    bool possible = true;
    for (int& i : v) cin >> i;

    for (int i = 1; i < n; i++) {
      if (s.count(i)) continue;
      if (v[i] < v[i - 1]) {
        possible = false;
        break;
      }
    }
    if (possible) cout << "YES\n";
    else cout << "NO\n";
  }
}
