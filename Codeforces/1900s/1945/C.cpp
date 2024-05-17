#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;
string a;

void solve() {
  cin >> n >> a;
  vi zeros(n + 1), ones(n + 1);
  for (int i = 0; i < n; i++) {
    zeros[i + 1] = zeros[i] + (a[i] == '0');
    ones[i + 1] = ones[i] + (a[i] == '1');
  }
  int ans = (ones[n] >= (n + 1) / 2) ? n : abs(n - 2 * (n - 1 + 1));
  int val = (ones[n] >= (n + 1) / 2) ? 0 : n;
  for (int i = 0; i < n; i++) {
    int zero = zeros[i + 1];
    int one = ones[n] - ones[i + 1];
    if (zero >= (i + 2) / 2 && one >= (n - i) / 2) {
      if (ans > abs(n - 2 * (i + 1))) {
        ans = abs(n - 2 * (i + 1));
        val = i + 1;
      } else if (ans == abs(n - 2 * (i + 1))) {
        val = min(val, i + 1);
      }
    }
  }
  cout << val << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
