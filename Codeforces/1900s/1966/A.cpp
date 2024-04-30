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
  vi a(n);
  unordered_map<int, int> mp;
  for (int &i : a) {
    cin >> i;
    mp[i]++;
  }
  if (n < k) cout << n << '\n';
  else {
    bool can = false;
    for (auto &[num, cnt] : mp) {
      if (cnt >= k) {
        can = true;
        break;
      }
    }
    if (can) cout << k - 1 << '\n';
    else cout << n << '\n';
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
