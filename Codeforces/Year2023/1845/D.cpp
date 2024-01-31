#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;
typedef vector<ii> vii;
typedef vector<ll> vll;

int t, n;

void solve() {
  cin >> n;
  vll v(n), prefix = {0};
  ll mn = 1e9, sum = 0, l = 0, k;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    sum += v[i];
    prefix.push_back(prefix.back() + v[i]);
    if (sum > 0) {
      l = i + 1;
      sum = 0;
    } else {
      if (sum < mn) {
        mn = sum;
        k = prefix[l];
      }
    }
  }
  cout << k << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
