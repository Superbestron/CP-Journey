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
  int ones = 0;
  for (int &i : a) {
    cin >> i;
    if (i == 1) ones++;
  }
  if (ones > 1) {
    cout << "NO\n";
    return;
  }
  sort(a.begin(), a.end());
  if (a[0] != a[1]) {
    cout << "YES\n";
  } else {
    for (int i = 2; i < n; i++) {
      if (a[i] % a[0]) {
        cout << "YES\n";
        return;
      }
    }
    cout << "NO\n";
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
