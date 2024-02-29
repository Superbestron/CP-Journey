#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;

int t, n, q, s, d, k;

void solve() {
  cin >> n >> q;
  vi a(n);
  for (int &i : a) cin >> i;
  int pivot = 1;
  while (pivot * pivot < n) pivot++;
  // pref is for prefix sum, prefi is for prefix sum * i
  vector<vll> pref(pivot + 1, vll(n + pivot)), prefi(pivot + 1, vll(n + pivot));
  for (int di = 1; di <= pivot; di++) {
    for (int j = 0; j < n; j++) {
      pref[di][di + j] = pref[di][j] + a[j];
      prefi[di][di + j] = prefi[di][j] + (ll) a[j] * (j / di + 1);
    }
  }
  for (int i = 0; i < q; i++) {
    cin >> s >> d >> k;
    s--;
    // solve directly
    if (d > pivot) {
      ll sum = 0, ctr = 1;
      for (int j = s; j <= s + (k - 1) * d; j += d) {
        sum += a[j] * ctr++;
      }
      cout << sum << ' ';
    } else {
      int end_idx = s + d * (k - 1);
      int factor = s / d;
      cout << prefi[d][end_idx + d] - prefi[d][s] - (pref[d][end_idx + d] - pref[d][s]) * factor << ' ';
    }
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
