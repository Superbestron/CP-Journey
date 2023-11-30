#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, m;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    deque<int> a(n - 1), b(n);
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    ll ops = 0;
    for (int i = n - 2, ctr = n - 1; i >= 0; i--, ctr--) {
      if (a[i] >= b[ctr]) {
        a.pop_back();
        b.pop_front();
        ops += m;
      }
    }
    bool can = true;
    m -= min(m, b[0] - 1);
    for (int i = 0; i < a.size(); i++) {
      if (a[i] >= b[i]) can = false;
      if (!can) ops += min(m, b[i + 1] - b[i]);
      m -= min(m, b[i + 1] - b[i]);
      if (m == 0) break;
    }
    cout << ops + m << '\n';
  }
}