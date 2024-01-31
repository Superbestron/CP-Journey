#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll tc, n;
  string s;
  cin >> tc;
  while (tc--) {
    deque<char> d;
    cin >> n >> s;
    unordered_map<char, int> mp;
    for (char c : s) {
      d.push_back(c);
      mp[c]++;
    }
    int end = n, start = 0;
    vector<int> ans;
    bool can = true;
    while (d.size() >= 2) {
      if (mp.size() == 1) {
        can = false;
        break;
      }
      char front = d.front();
      char back = d.back();
      if (front != back) {
        d.pop_front();
        d.pop_back();
        end--;
        mp['0']--;
        if (mp['0'] == 0) mp.erase('0');
        mp['1']--;
        if (mp['1'] == 0) mp.erase('1');
        start++;
      } else if (front == '1') {
        d.pop_back();
        d.push_front('1');
        ans.push_back(start);
        start++;
        end++;
      } else {
        d.pop_front();
        d.push_back('0');
        ans.push_back(end);
        end++;
        start++;
      }
    }
    if (mp.size() == 1) {
      cout << -1 << '\n';
    } else if (can) {
      cout << ans.size() << '\n';
      for (int i : ans) cout << i << ' ';
      cout << '\n';
    }
  }
}