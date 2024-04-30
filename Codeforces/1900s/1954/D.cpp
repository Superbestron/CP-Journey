#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n;
const int MOD = 998244353;

void solve() {
  cin >> n;
  vi a(n);
  int sum = 0, ans = 0;
  for (int &i : a) {
    cin >> i;
    sum += i;
  }
  vi memo(sum + 1);
  memo[0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = sum; j >= a[i]; j--) {
      memo[j] = (memo[j] + memo[j - a[i]]) % MOD;
    }
  }
  for (int i = 0; i <= sum; i++) {
    ans = ((ll) (i + 1) / 2 * memo[i] + ans) % MOD;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < a[i]; j++) {
      ans = ((ll) ans + (a[i] - (ll) (a[i] + j + 1) / 2) * memo[j] + MOD) % MOD;
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
