
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<ll> factorial({1, 1});
  for (int i = 2; i < 20; i++) factorial.emplace_back(factorial.back() * i);
  int tc;
  cin >> tc;
  while (tc--) {
    string s, ans;
    ll pos;
    cin >> s >> pos;
    set<char> avail_char;
    for (char c : s) avail_char.emplace(c);
    for (int i = s.size() - 1; i >= 0; i--) {
      int idx = pos / factorial[i];
      auto it = avail_char.begin();
      for (int j = 0; j < idx; j++) it++;
      ans.push_back(*it);
      avail_char.erase(it);
      pos -= factorial[i] * idx;
    }
    cout << ans << '\n';
  }
}
