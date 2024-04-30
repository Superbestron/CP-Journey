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
  vi a(n);
  unordered_map<int, int> mp;
  for (int &i : a) {
    cin >> i;
    mp[i]++;
  }
  int ans = 0;
  for (auto &[num, cnt] : mp) {
    ans += cnt / 3;
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
