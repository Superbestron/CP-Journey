#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<string> split(string& s, char delimiter) {
  size_t pos;
  string token;
  vector<string> arr;
  if (s.empty()) return arr;
  while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    arr.emplace_back(token);
    s.erase(0, pos + 1);
  }
  arr.emplace_back(s);
  return arr;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  string s;
  while (cin >> n && n != 0) {
    cin.ignore();
    int mini = 0, maxi = INT32_MAX, factors = 1;
    while (n--) {
      getline(cin, s);
      vector<string> v(split(s, ' '));
      int num = stoi(v[2]);
      if (v[0][0] == 'l') {
        maxi = min(maxi, num);
      } else if (v[0][0] == 'g') {
        mini = max(mini, num);
      } else {
        factors = lcm(factors, num);
      }
    }
    if (maxi == INT32_MAX) cout << "infinite\n";
    else {
      vector<int> ans;
      for (int i = factors; i < maxi; i += factors) {
        if (i <= mini) continue;
        ans.push_back(i);
      }
      if (ans.empty()) cout << "none";
      else for (int i : ans) cout << i << ' ';
      cout << '\n';
    }
  }
}
