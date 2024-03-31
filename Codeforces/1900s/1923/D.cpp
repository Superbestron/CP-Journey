#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a(n), output(n, 1e9);
  for (int &i : a) cin >> i;
  for (int tc = 0; tc < 2; tc++) {
    // [l...r] = pref[r + 1] - pref[l]
    vll pref(n + 1), diff(n, -1);
    for (int i = 0; i < n; i++) {
      pref[i + 1] = pref[i] + a[i];
      if (i == 0) continue;
      diff[i] = diff[i - 1];
      if (a[i - 1] != a[i]) diff[i] = i - 1;
    }
    auto f = [&](int idx, int tar) {
      int lo = 0, hi = idx;
      while (hi > lo) {
        int mid = lo + (hi - lo + 1) / 2;
        ll sum = pref[idx + 1] - pref[mid];
        (sum > tar) ? lo = mid : hi = mid - 1;
      }
      ll sum = pref[idx + 1] - pref[lo];
      if (sum > tar) return lo;
      else return -1;
    };
    for (int i = 1; i < n; i++) {
      if (a[i - 1] > a[i]) {
        output[(tc == 0) ? i : n - i - 1] = 1;
        continue;
      }
      int closest_left_diff = diff[i - 1];
      if (closest_left_diff != -1) {
        ll closest_left_sum_gt_tar = f(i - 1, a[i]);
        if (closest_left_sum_gt_tar != -1) {
          output[(tc == 0) ? i : n - i - 1]
            = min((ll) output[(tc == 0) ? i : n - i - 1],
                  max((ll) i - closest_left_diff, i - closest_left_sum_gt_tar));
        }
      }
    }
    reverse(a.begin(), a.end());
  }
  for (int i : output) {
    if (i == 1e9) cout << "-1 ";
    else cout << i << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
