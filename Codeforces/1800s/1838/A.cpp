#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;

void solve() {
  cin >> n;
  vi a(n);
  bool has_neg = false;
  int neg;
  int mx = 0;
  for (int &i : a) {
    cin >> i;
    if (i < 0) {
      neg = i;
      has_neg = true;
    }
    mx = max(mx, i);
  }
  if (has_neg) cout << neg << '\n';
  else cout << mx << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
