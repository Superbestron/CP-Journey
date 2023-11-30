#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> iii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N; cin >> N;
  vector<iii> v(N);
  for (int i = 0; i < N; i++) {
    int x1, x2, y;
    cin >> y >> x1 >> x2;
    v.emplace_back(y, x1, x2);
  }
  sort(v.begin(), v.end(), greater());
  int ans = 0;
  for (int i = 0; i < N; i++) {
    auto &[y, x1, x2] = v[i];
    bool left = false, right = false;
    for (int j = i + 1; j < N; j++) {
      auto &[y_j, x1j, x2j] = v[j];
      if (!left && x1j <= x1 && x1 + 1 <= x2j) {
        ans += y - y_j;
        left = true;
      }
      if (!right && x1j <= x2 - 1 && x2 <= x2j) {
        ans += y - y_j;
        right = true;
      }
    }
    if (!left) ans += y;
    if (!right) ans += y;
  }
  cout << ans << '\n';
}
