#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m, k;

void solve() {
  cin >> n >> m >> k;
  int temp = (n + (m - 1)) / m;
  if (temp + k >= n) cout << "NO\n";
  else cout << "YES\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
