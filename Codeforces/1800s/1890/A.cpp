#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, n, val;
  cin >> t;
  while (t--) {
    cin >> n;
    unordered_map<int, int> m;
    for (int i = 0; i < n; i++) {
      cin >> val;
      m[val]++;
    }
    if (m.size() > 2) {
      cout << "NO\n";
    } else if (m.size() == 2) {
      vector<int> vec;
      for (auto& [i, cnt] : m) {
        vec.push_back(cnt);
      }
      if (n % 2 == 0) {
        if (vec[0] == vec[1]) cout << "YES\n";
        else cout << "NO\n";
      } else {
        if (abs(vec[0] - vec[1]) == 1) cout << "YES\n";
        else cout << "NO\n";
      }
    } else {
      cout << "YES\n";
    }
  }
}
