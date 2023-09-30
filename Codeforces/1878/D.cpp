#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, k, q;
  string s;
  cin >> t;
  while (t--) {
    cin >> n >> k >> s;
    vector<int> l(k), r(k);
    for (int& i : l) {
      cin >> i; i--;
    }
    for (int& i : r) {
      cin >> i; i--;
    }
    cin >> q;
    vector<int> x(q), cnt(n);
    for (int& i : x) {
      cin >> i;
      cnt[i - 1]++;
    }
    string ans;
    for (int i = 0; i < k; i++) {
      int left = l[i], right = r[i], sum = 0;
      string substr(s.substr(left, right - left + 1));
      for (int j = left; j <= (right + left) / 2; j++) {
        sum += cnt[j] + cnt[right + left - j];
        if (sum & 1) swap(substr[j - left], substr[right - j]);
      }
      ans += substr;
    }
    cout << ans << '\n';
  }
}