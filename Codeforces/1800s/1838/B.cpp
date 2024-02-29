#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;

void solve() {
  cin >> n;
  vi a(n);
  int one_pos, two_pos, n_pos;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] == 1) one_pos = i + 1;
    else if (a[i] == 2) two_pos = i + 1;
    else if (a[i] == n) n_pos = i + 1;
  }
  if (n_pos > one_pos && n_pos < two_pos || n_pos < one_pos && n_pos > two_pos) cout << "1 1\n";
  else if (n_pos < one_pos && n_pos < two_pos) cout << n_pos << ' ' << min(one_pos, two_pos) << '\n';
  else cout << n_pos << ' ' << max(one_pos, two_pos) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
