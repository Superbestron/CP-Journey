#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

ll t, a, b, r;

void solve() {
  cin >> a >> b >> r;
  if (a < b) swap(a, b);
  ll ans = 2e18, x, curr_ans = 0;
  int highest_bit_a = -1;
  for (int i = 60; i >= 0; i--) {
    // same bit no point
    ll bit_value = 0;
    if (a & (1LL << i) == b & (1LL << i)) continue;
    if (a & (1LL << i) && (b & (1LL << i)) == 0) {
      highest_bit_a = i;
      for (int j = i - 1; j >= 0; j--) {
        if (a & (1LL << j) == b & (1LL << j)) continue;
        else if (a & (1LL << j) && (b & (1LL << j)) == 0) { // 1 top, 0 btm
          if (bit_value + (1LL << j) <= r) bit_value += (1LL << j);
        }
      }
    }
//    else if (highest_bit_a != -1) {
//      if (bit_value + (1LL << i) <= r) bit_value += (1LL << i);
//      for (int j = i - 1; j >= 0; j--) {
//        if (a & (1LL << j) == b & (1LL << j)) continue;
//        else if (a & (1LL << j) && (b & (1LL << j)) == 0) { // 1 top, 0 btm
//          if (bit_value + (1LL << j) <= r) bit_value += (1LL << j);
//        }
//      }
//    }
    ll temp = (a ^ bit_value) - (b ^ bit_value);
    assert(temp >= 0);
    if (temp < ans) {
      ans = temp;
      x = bit_value;
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
