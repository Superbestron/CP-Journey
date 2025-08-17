#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

inline void solve() {
  cin >> n >> k;
  vector<string> AL(n);
  for (auto &row : AL) {
    cin >> row;
  }
  for (int i = 0; i < n; i += k) {
    for (int j = 0; j < n; j += k) {
      cout << AL[i][j];
    }
    cout << '\n';
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
