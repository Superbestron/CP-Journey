#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, k;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    vector<int> v(n);
    bool can = false;
    for (int i = 0; i < n; i++) {
      cin >> v[i];
      if (v[i] == k) {
        can = true;
      }
    }
    if (can) cout << "YES\n";
    else cout << "NO\n";
  }
}