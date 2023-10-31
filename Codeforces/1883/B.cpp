#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, k;
  string s;
  cin >> t;
  while (t--) {
    cin >> n >> k >> s;
    unordered_map<char, int> m;
    for (char c : s) {
      m[c]++;
    }
    int one = 0, sz = s.size();
    for (auto &[c, cnt] : m) {
      if (cnt & 1) one++;
    }
    if (k < one - 1) {
      cout << "NO\n";
    } else {
      k -= one - 1;
      sz -= one - 1;
      if (k > sz) cout << "NO\n";
      cout << "YES\n";
    }
  }
}