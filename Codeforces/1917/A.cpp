#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;

void solve() {
  cin >> n;
  vi a(n);
  int neg_count = 0;
  bool has_zero = false;
  vi idx;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] < 0) {
      neg_count++;
      idx.push_back(i);
    }
    if (a[i] == 0) has_zero = true;
  }
  if (neg_count & 1) {
    cout << 0 << '\n';
  } else {
    if (has_zero) cout << 0 << '\n';
    else {
      cout << 1 << '\n';
      cout << "1 0\n";
    }
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
