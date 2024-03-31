#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

ll t, n, m;

bool check_power_2(ll x) {
  while (x > 1) {
    if (x & 1) return false;
    x >>= 1;
  }
  return true;
}

void solve() {
  cin >> n >> m;
  if (check_power_2(n)) {
    cout << "-1\n"; return;
  }
  int first_idx = -1, second_idx = -1, first_idx_m = -1;
  for (int i = 62; i >= 0; i--) {
    if (first_idx == -1) {
      if (n & (1LL << i)) {
        first_idx = i;
      }
    } else if (second_idx == -1) {
      if (n & (1LL << i)) {
        second_idx = i;
      }
    }
    if (first_idx_m == -1) {
      if (m & (1LL << i)) {
        first_idx_m = i;
      }
    }
  }

  if (first_idx_m < first_idx && first_idx_m > second_idx) {
    cout << "-1\n"; return;
  }

  if (first_idx_m == first_idx) {
    cout << 1 << '\n' << n << ' ' << m << '\n';
  } else {
    if ((1LL << (second_idx + 1)) - 1 == m) cout << 1 << '\n' << n << ' ' << m << '\n';
    else cout << 2 << '\n' << n << ' ' << (1LL << (second_idx + 1)) - 1 << ' ' << m << '\n';
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
