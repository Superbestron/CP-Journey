#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int t, n, x, val;

inline void solve() {
  cin >> n >> x;
  vector<int> a;
  vector<ii> b;
  for (int i = 0; i < n; i++) {
    cin >> val;
    a.push_back(val);
  }
  for (int i = 0; i < n; i++) {
    cin >> val;
    b.emplace_back(val, i);
  }

  sort(a.begin(), a.end(), greater<>());
  sort(b.begin(), b.end());

  for (int i = 0, j = x - 1; i < x; j--, i++) {
    if (a[i] <= b[j].first) {
      cout << "NO\n";
      return;
    }
    b[j].second = i;
  }
  for (int i = x, j = n - 1; i < n; i++, j--) {
    if (b[j].first < a[i]) {
      cout << "NO\n";
      return;
    }
    b[j].second = i;
  }
  cout << "YES\n";

  sort(b.begin(), b.end(), [&](ii &i, ii &j) {
    return i.second < j.second;
  });

  for (auto &[i, id] : b) cout << i << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
