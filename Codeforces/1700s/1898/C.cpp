#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

ll t, n, m, k;
char s[2] = {'R', 'B'};

void solve() {
  cin >> n >> m >> k;
  if (n + m - 2 > k) {
    cout << "NO\n";
    return;
  }
  if ((k - (n + m - 2)) % 2 == 1) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m - 1; ++j) cout << s[j % 2] << ' ';
    cout << '\n';
  }
  int st = m - 1;
  for (int i = 1; i <= n - 1; ++i) {
    for (int j = 1; j <= m - 1; ++j) cout << 'R' << ' ';
    cout << s[(st + i) % 2] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
