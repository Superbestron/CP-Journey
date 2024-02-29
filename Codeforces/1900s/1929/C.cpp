#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

ll t, k, x, a;

void solve() {
  cin >> k >> x >> a;
  ll sum = 0, current_bet = 1;
  k--;
  for (int i = 0; i <= x; i++) {
    current_bet = sum / k; // needs to win > sum
    current_bet++;
    sum += current_bet;
    if (sum > a) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
