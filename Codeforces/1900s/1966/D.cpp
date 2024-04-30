#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

void solve() {
  cin >> n >> k;
  vi ans;
  int l = 0;
  while ((1 << (l + 1)) <= k) l++;
  ans.push_back(k - (1 << l));
  ans.push_back(k + 1);
  ans.push_back(k + 1 + (1 << l));
  for (int i = 0; i <= 19; i++) {
    if (i != l) ans.push_back(1 << i);
  }
  cout << ans.size() << '\n';
  for (int i : ans) cout << i << ' ';
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
