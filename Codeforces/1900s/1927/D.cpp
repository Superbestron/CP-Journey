#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n, q;

void solve() {
  cin >> n;
  vi a;
  int prev = -1;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (x != prev) a.push_back(i + 1);
    prev = x;
  }
  cin >> q;
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    int partition_l = upper_bound(a.begin(), a.end(), l) - a.begin();
    int partition_r = upper_bound(a.begin(), a.end(), r) - a.begin();
    partition_l--; partition_r--;
    if (partition_l == partition_r) cout << "-1 -1\n";
    else cout << l << ' ' << a[partition_l + 1] << '\n';
  }
  cout << '\n';
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
