#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, l, r;
  cin >> t;
  while (t--) {
    cin >> n;
    set<pair<int, int>> s;
    vector<tuple<int, int, int>> ans;
    for (int i = 0; i < n; i++) {
      cin >> l >> r;
      s.emplace(l, r);
    }
    for (auto& [le, ri] : s) {
      if (le == ri) {
        ans.emplace_back(le, ri, le);
      } else {
        for (int i = le; i <= ri; i++) {
          if (i == le) {
            if (s.count({le + 1, ri})) {
              ans.emplace_back(le, ri, i);
              break;
            }
          } else if (i == ri) {
            if (s.count({le, ri - 1})) {
              ans.emplace_back(le, ri, i);
              break;
            }
          } else {
            if (s.count({le, i - 1}) && s.count({i + 1, ri})) {
              ans.emplace_back(le, ri, i);
              break;
            }
          }
        }
      }
    }
    for (auto& [l, r, val] : ans) cout << l << ' ' << r << ' ' << val << '\n';
    cout << '\n';
  }
}