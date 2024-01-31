#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, n, k;

void solve() {
  cin >> n >> k;
  string s;
  for (int i = 0; i < k; i++) s += (char) ('a' + i);
  for (int i = 0; i < n; i++) {
    cout << s;
  }
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
