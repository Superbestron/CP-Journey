#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

void solve() {
  cin >> n;
  vi a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  auto check = [&]() {
    for (int i = 0; i < n; i++) {
      if (a[i] > b[i]) return false;
    }
    return true;
  };
  int ans = 0;
  while (!check()) {
    a.pop_back();
    a.push_back(1);
    sort(a.begin(), a.end());
    ans++;
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
