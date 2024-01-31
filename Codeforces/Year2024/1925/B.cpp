#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t, x, n;

vi printDivisors(int n) {
  vi ans;
  for (int i = 1; i <= sqrt(n); i++) {
    if (n % i == 0) {
      if (n / i == i) ans.push_back(i);
      else {
        ans.push_back(i);
        ans.push_back(n / i);
      }
    }
  }
  return ans;
}

void solve() {
  cin >> x >> n;
  vi factors = printDivisors(x);
  sort(factors.begin(), factors.end());
  auto it = lower_bound(factors.begin(), factors.end(), n);
  cout << x / (*it) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
