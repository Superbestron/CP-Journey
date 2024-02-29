#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

int t, n;

void solve() {
  cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  int num = a[0], cnt = 0, idx = 0, idx2 = n - 1;
  while (idx < n && a[idx] == num) {
    cnt++;
    idx++;
  }
  if (idx != n) {
    while (idx2 != idx && a[idx2] == num) {
      cnt++;
      idx2--;
    }
  }
  int ans1 = n - cnt;  num = a[n - 1], cnt = 0, idx = n - 1, idx2 = 0;
  while (idx >= 0 && a[idx] == num) {
    cnt++;
    idx--;
  }
  if (idx >= 0) {
    while (idx != idx2 && a[idx2] == num) {
      cnt++;
      idx2++;
    }
  }

  cout << min(ans1, n - cnt) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
