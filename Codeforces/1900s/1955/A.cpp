#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, a, b;

void solve() {
  cin >> n >> a >> b;
  if (a * 2 <= b) {
    cout << n * a << '\n';
  } else {
    cout << n / 2 * b + (n & 1) * a << '\n';
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
