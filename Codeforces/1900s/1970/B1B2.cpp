#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  if (n == 2) {
    int i, j;
    cin >> i >> j;
    if (i != j && i && j) { // case: 1,2
      cout << "NO\n";
    } else {
      cout << "YES\n";
      cout << "1 1\n";
      if (i == j) {
        if (i == 1) cout << "1 2\n2 1";
        else if (i == 2) cout << "2 2\n2 1";
        else cout << "2 2\n1 2";
      } else { // 0,1 / 1,0 / 2,0 / 0,2
        cout << (i + j == 2 ? "2 2\n" : "1 2\n");
        cout << (i ? "2 2" : "1 1");
      }
    }
    return 0;
  }
  cout << "YES\n";
  vii v(n);
  unordered_set<int> s;
  bool r = false;
  for (int i = 0; i < n; i++) {
    cin >> v[i].first;
    if (s.count(v[i].first)) r = true;
    else s.insert(v[i].first);
    v[i].second = i + 1;
  }
  sort(v.begin(), v.end());
  viii ans(n + 1);
  if (!r) { // strictly ascending
    auto &[dl, idxl] = v[0];
    auto &[xl, yl, cl] = ans[idxl];
    xl = 1, yl = 1;
    if (!v[0].first) {// contains 0
      cl = idxl;
      for (int i = 1; i < n; i++) {
        auto &[d, idx] = v[i];
        auto &[x, y, c] = ans[idx];
        x = 1, y = i + 1, c = idxl;
      }
    } else { // no 0, point to right
      auto &[dr, idxr] = v[1];
      auto &[xr, yr, cr] = ans[idxr];
      cl = idxr;
      for (int i = 1; i < n; i++) {
        auto &[d, idx] = v[i];
        auto &[x, y, c] = ans[idx];
        x = i, y = i + 1, c = idxl;
      }
    }
  } else { // repeats
    bool flip = false, inc = false;
    int py = n;
    for (int i = n - 1; i >= 0; i--) {
      auto &[d, idx] = v[i];
      auto &[x, y, c] = ans[idx];
      if (flip) {
        auto &[dr, idxr] = v[i + 1];
        auto &[xr, yr, cr] = ans[idxr];
        x = i + 1, y = yr + (d ? (inc ? d - 1 : -d + 1) : 0), c = d ? idxr : idx;
      } else {
        auto &[dl, idxl] = v[i - 1];
        auto &[xl, yl, cl] = ans[idxl];
        x = i + 1, y = py, c = d ? idxl : idx;
        if (dl == d || !dl || !d) {
          flip = true;
          xl = i, yl = y + (d ? (inc ? d - 1 : -d + 1) : 0), cl = dl ? idx : idxl;
          i--;
        } else {
          py += inc ? d - 1 : -d + 1;
        }
      }
      inc = !inc;
    }
  }
  for (int i = 1; i <= n; i++) {
    auto &[x, y, c] = ans[i];
    cout << x << ' ' << y << '\n';
  }
  for (int i = 1; i <= n; i++) {
    auto &[x, y, c] = ans[i];
    cout << c << ' ';
  }
}
