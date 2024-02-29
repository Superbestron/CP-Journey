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
  int sum = 0;
  for (int &i : a) {
    cin >> i;
    sum += i;
  }
  bool can = true;
  int each = sum / n, supposed = 0;
  sum = 0;
  for (int i = n - 1; i >= 0; i--) {
    sum += a[i];
    supposed += each;
    if (sum > supposed) {
      can = false;
      break;
    }
  }
  if (can) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
