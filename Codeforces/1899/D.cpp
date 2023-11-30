#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n, val;

ll com(int i, int m){
  return (ll)i*(i-1)/2;
}

void solve() {
  cin >> n;
  vector<int> a(n);
  map<int, int> m;
  for (int &i : a) {
    cin >> i;
    if (i == 1) m[2]++;
    else m[i]++;
  }
  ll ans = 0;
  for (auto &[num, cnt] : m) {
    ans += com(cnt, 2);
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
