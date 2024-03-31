#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

void solve() {
  cin >> n >> k;
  vi a(n);
  int l = 1, r = n;
  for (int i = 0; i < k; i++) {
    for (int j = i; j < n; j += k) {
      if (i % 2 == 0) a[j] = l++;
      else a[j] = r--;
    }
  }
  for (int i : a) cout << i << ' ';
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
