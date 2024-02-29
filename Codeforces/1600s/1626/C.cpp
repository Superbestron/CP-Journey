#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> k(n), h(n);
    vector<pair<int, int>> v;
    for (int &i : k) cin >> i;
    for (int &i : h) cin >> i;
    for (int i = 0; i < n; i++) {
      int ki = k[i], hi = h[i];
      v.emplace_back(ki - hi + 1, ki);
    }
    sort(v.begin(), v.end());
    vector<pair<int, int>> output;
    output.push_back(v[0]);
    for (int i = 1; i < n; i++) {
      auto& curr = output.back();
      if (v[i].first <= curr.second) {
        curr.second = max(curr.second, v[i].second);
      } else {
        output.push_back(v[i]);
      }
    }
    ll sum = 0;
    for (auto& p : output) {
      ll len = p.second - p.first + 1;
      sum += len * (2 + (len - 1)) / 2;
    }
    cout << sum << '\n';
  }
}