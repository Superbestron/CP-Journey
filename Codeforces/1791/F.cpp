#include <bits/stdc++.h>
using namespace std;

inline int convert(int n) {
  int ret = 0;
  while (n) {
    ret += n % 10;
    n /= 10;
  }
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, q, query, l, r, x;
  cin >> t;
  while (t--) {
    cin >> n >> q;
    vector<int> v(n);
    set<int> m;
    for (int i = 0; i < v.size(); i++) {
      cin >> v[i];
      if (v[i] > 9) m.insert(i);
    }
    while (q--) {
      cin >> query;
      if (query == 1) {
        cin >> l >> r;
        l--; r--;
        for (auto it = m.lower_bound(l); it != m.end() && *it <= r;) {
          int idx = *it;
          v[idx] = convert(v[idx]);
          if (v[idx] < 10) it = m.erase(it);
          else it++;
        }
      } else {
        cin >> x;
        x--;
        cout << v[x] << '\n';
      }
    }
  }
}