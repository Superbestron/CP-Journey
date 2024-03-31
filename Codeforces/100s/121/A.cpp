#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  int limit = sqrt(2 * n);
  int left = 1, right = limit;
  while (left <= right) {
    int l_val = left * (left + 1) / 2;
    int r_val = right * (right + 1) / 2;
    if (l_val + r_val == n) {
      cout << "YES\n";
      return;
    } else if (l_val + r_val < n) left++;
    else right--;
  }
  cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
