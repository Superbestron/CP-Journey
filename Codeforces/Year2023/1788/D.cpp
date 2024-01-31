#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

vector<ll> modTable;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, sum = 0;
  modTable.push_back(1);
  cin >> n;
  for (int i = 1; i < n; i++) {
    modTable.push_back((modTable.back() << 1) % MOD);
  }
  vector<int> v(n);
  for (int &i : v) cin >> i;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int L = v[i], R = v[j];
      int dist = R - L;
      int left_pts = 0, right_pts = 0;
      if (i != 0) left_pts = lower_bound(v.begin(), v.end(), L - dist) - v.begin();
      if (j != n - 1) right_pts = n - (int) (lower_bound(v.begin(), v.end(), R + dist) - v.begin());
      sum = (sum + modTable[left_pts + right_pts]) % MOD;
    }
  }
  cout << sum;
}
