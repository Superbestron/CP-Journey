#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n;

void solve() {
  cin >> n;
  vi a(n), dist;
  for (int &i : a) cin >> i;
  int and_sum = a[0];
  int ans = 0;
  for (int i = 0; i < n; i++) {
    and_sum &= a[i];
    if (and_sum == 0) {
      and_sum = a[i + 1];
      ans++;
    }
  }
  cout << max(1, ans) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
