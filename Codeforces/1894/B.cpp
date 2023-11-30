#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n;

void solve() {
  cin >> n;
  vector<int> v(n);
  unordered_map<int, int> m;
  for (int &i : v) {
    cin >> i;
    m[i]++;
  }
  vector<int> can;
  for (auto& [num, cnt] : m) {
    if (cnt >= 2) can.push_back(num);
    if (can.size() == 2) break;
  }
  if (can.size() < 2) {
    cout << -1 << '\n';
    return;
  }
  bool seen_first = false, seen_second = false;
  for (int i : v) {
    if (i == can[0]) {
      if (seen_first) {
        cout << '1' << ' ';
      } else {
        cout << '2' << ' ';
        seen_first = true;
      }
    } else if (i == can[1]) {
      if (seen_second) {
        cout << '1' << ' ';
      } else {
        cout << '3' << ' ';
        seen_second = true;
      }
    } else cout << '1' << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}