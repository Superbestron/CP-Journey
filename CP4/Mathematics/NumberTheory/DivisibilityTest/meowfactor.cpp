#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll pow9(ll x) {
  ll ans = 1;
  for (int i = 0; i < 9; i++) ans *= x;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n; cin >> n;
  for (int i = 128; i >= 1; i--) {
    ll xpow = pow9(i);
    if (n % xpow == 0) {
      cout << i;
      return 0;
    }
  }
}