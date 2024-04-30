#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int c, a, val, times = 0;
  cin >> c >> a;
  vi A(a), ans, C(c, -1);
  set<ii> found;
  for (int &i : A) {
    cin >> i;
  }
  auto read = [&](int mid) {
    cout << "Q " << mid + 1 << endl;
    cin >> val;
    C[mid] = val;
    found.emplace(val, mid);
  };
  read(0); read(c - 1);
  for (int i : A) {
    if (i >= C.back()) {
      ans.push_back(c);
      continue;
    }
    auto lo_it = found.lower_bound({i, 1e9});
    int lo = prev(lo_it)->second;
    auto hi_it = found.lower_bound({i, 1e9});
    int hi = hi_it->second - 1;
    while (hi > lo) {
      int mid = lo + (hi - lo + 1) / 2;
      if (C[mid] == -1) {
        read(mid);
      } else val = C[mid];
      if (val < i) lo = mid;
      else if (val == i) {
        lo = mid; break;
      } else hi = mid - 1;
    }
    ans.push_back(lo + 1);
  }
  cout << "A ";
  for (int i : ans) cout << i << ' ';
  cout << endl;
}
