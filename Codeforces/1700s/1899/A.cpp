#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n;

void solve() {
  cin >> n;
  if (n % 3 == 0) cout << "Second\n";
  else cout << "First\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}