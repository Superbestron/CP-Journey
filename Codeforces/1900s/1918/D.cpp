#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a(n);
  for (ll &i : a) cin >> i;
  ll lo = 0, hi = 1e14;
  while (hi > lo) {
    ll mid = lo + (hi - lo) / 2;
    multiset<ll> pos;
    // memo[i] is min sum of blocked elems in suffix up to i if pos i is blocked, and on each of the subsegments
    // without blocked elements, the sum of elements is less than or equal to m.
    vi memo(n + 1);
    int r = n;
    ll sum = 0;
    pos.insert(0);
    for (int l = n - 1; l >= 0; l--) {
      while (sum > mid) {
        sum -= a[r - 1];
        auto it = pos.find(memo[r]);
        pos.erase(it);
        r--;
      }
      memo[l] = *pos.begin() + a[l];
      pos.insert(memo[l]);
      sum += a[l];
    }
    sum = 0;
    bool yes = false;
    for (int i = 0; i < n; i++) {
      if (sum <= mid && memo[i] <= mid) yes = true;
      sum += a[i];
    }
    if (yes) hi = mid;
    else lo = mid + 1;
  }
  cout << lo << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
