#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, m;
  cin >> t;
  start:
  while (t--) {
    cin >> n >> m;
    string x, s;
    cin >> x >> s;
    if (x.find(s) != string::npos) {
      cout << 0 << '\n';
      continue;
    }
    for (int i = 1; i <= 5; i++) {
      x += x;
      if (x.find(s) != string::npos) {
        cout << i << '\n';
        goto start;
      }
    }
    cout << -1 << '\n';
  }
}