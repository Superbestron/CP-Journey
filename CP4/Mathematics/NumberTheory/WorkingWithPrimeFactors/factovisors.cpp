#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  while (cin >> n >> m) {
    bool possible;
    if (m == 0) possible = false;
    else if (m <= n) possible = true;
    else {
      unordered_map<int, int> mp;
      int num = m, PF = 2;
      while (num > 1 && (ll) PF * PF <= m) {
        while (num % PF == 0) {
          mp[PF]++;
          num /= PF;
        }
        PF++;
      }
      if (num > 1) mp[num]++;
      possible = true;
      for (auto &[p, cnt] : mp) {
        int ans = 0;
        for (int prime = p; prime <= n; prime *= p) {
          ans += n / prime;
        }
        if (ans < cnt) {
          possible = false;
          break;
        }
      }
    }
    if (possible) cout << m << " divides " << n << "!\n";
    else cout << m << " does not divide " << n << "!\n";
  }
}