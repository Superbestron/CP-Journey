#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, m;
  cin >> t;
  class Compare {
   public:
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
      if (p1.first == p2.first) return p1.second < p2.second;
      return p1.first < p2.first;
    };
  };
  class Compare2 {
   public:
    bool operator() (const pair<int, int>& p1, const pair<int, int>& p2) {
      if (p1.second == p2.second) return p1.first < p2.first;
      return p1.second < p2.second;
    };
  };
  while (t--) {
    cin >> n >> m;
    vector<pair<int, int>> v(n);
    for (auto& [x, y] : v) {
      cin >> x >> y;
      x--; y--;
    }
    sort(v.begin(), v.end(), Compare());
    set<pair<int, int>, Compare2> s;
    int ans = 0, ones = 0, last = 0;
    for (int i = 0; i < n; i++) {
      s.insert(v[i]);
      if (v[i].first == 0) ones++;
      if (v[i].second == m - 1) last++;
      while (!s.empty() && (*s.begin()).second < v[i].first) {
        if ((*s.begin()).first == 0) ones--;
        if ((*s.begin()).second == m - 1) last--;
        s.erase(s.begin());
      }
      ans = max(ans, (int) s.size() - min(ones, last));
    }
    cout << ans << '\n';
  }
}