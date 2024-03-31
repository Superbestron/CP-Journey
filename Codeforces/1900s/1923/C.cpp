#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, q;

void solve() {
  cin >> n >> q;
  vi a(n);
  for (int &i : a) cin >> i;
  vll pref1(n + 1), pref(n + 1);
  for (int i = 0; i < n; i++) {
    pref1[i + 1] += pref1[i] + (a[i] == 1);
    pref[i + 1] += pref[i] + a[i];
  }
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    l--; r--;
    int len = r - l + 1;
    ll count1 = pref1[r + 1] - pref1[l];
    ll sum = pref[r + 1] - pref[l];
    ll counto = len - count1;
    if (count1 == len || len == 1) {
      cout << "NO\n";
      continue;
    }
    if (count1 <= sum - count1 - counto) {
      cout << "YES\n";
    } else cout << "NO\n";
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
