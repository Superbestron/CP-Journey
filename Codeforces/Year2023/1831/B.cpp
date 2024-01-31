#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> a(n), b(n);
    unordered_map<int, int> a_m, b_m;
    unordered_set<int> s;
    for (int &i : a) {
      cin >> i;
      s.insert(i);
    }
    int prev = -1, cnt = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] == prev) {
        cnt++;
      } else {
        if (prev != -1) a_m[prev] = max(a_m[prev], cnt);
        cnt = 1;
      }
      prev = a[i];
    }
    a_m[prev] = max(a_m[prev], cnt);
    for (int &i : b) {
      cin >> i;
      s.insert(i);
    }
    prev = -1, cnt = 0;
    for (int i = 0; i < n; i++) {
      if (b[i] == prev) {
        cnt++;
      } else {
        if (prev != -1) b_m[prev] = max(b_m[prev], cnt);
        cnt = 1;
      }
      prev = b[i];
    }
    b_m[prev] = max(b_m[prev], cnt);
    int ans = 0;
    for (int i : s) {
      ans = max(ans, a_m[i] + b_m[i]);
    }
    cout << ans << '\n';
  }
}
