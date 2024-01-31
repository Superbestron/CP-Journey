#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      cout << 1000 + i << ' ';
    }
    cout << '\n';
  }
}