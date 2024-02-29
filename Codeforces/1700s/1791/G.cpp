#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<ll, int> ii;
typedef vector<ii> vii;

const int INF = 1e9;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, c;
  cin >> t;
  while (t--) {
    cin >> n >> c;
    vi a(n);
    vii b(n);
    for (int &i : a) cin >> i;
    for (int i = 0; i < n; i++) {
      b[i] = {min(a[i] + i + 1, n - i + a[i]), i};
    }
    sort(b.begin(), b.end());
    for (int i = 1; i < n; i++) {
      b[i].first += b[i - 1].first;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int actual_idx = b[i].second;
      if (a[actual_idx] + actual_idx + 1 > c) continue;
      ll curr = c - (a[actual_idx] + actual_idx + 1);
      int idx = upper_bound(b.begin(), b.end(), make_pair(curr, INF)) - b.begin();
      if (i < idx) {
        curr += min(a[actual_idx] + actual_idx + 1, n - actual_idx + a[actual_idx]);
        int idx2 = upper_bound(b.begin(), b.end(), make_pair(curr, INF)) - b.begin();
        ans = max(ans, idx2);
      } else {
        ans = max(ans, 1 + idx);
      }
    }
    cout << ans << '\n';
  }
}
