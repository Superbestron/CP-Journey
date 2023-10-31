#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll t, n, q, val;
  cin >> t;
  while (t--) {
    cin >> n >> q;
    vector<int> a(n), x;
    for (int &i : a) cin >> i;
    unordered_set<int> s;
    for (int i = 0; i < q; i++) {
      cin >> val;
      if (!s.count(val)) {
        s.insert(val);
        x.push_back(val);
      }
    }
    for (int i : x) {
      int divisible = 1 << i;
      for (int j = 0; j < n; j++) {
        if (a[j] % divisible == 0) {
          a[j] += (divisible >> 1);
        }
      }
    }
    for (int i : a) cout << i << ' ';
    cout << '\n';
  }
}
