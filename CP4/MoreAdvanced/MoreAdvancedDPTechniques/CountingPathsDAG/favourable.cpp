#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

int T, S, N, a, b;
string s;
vector<vector<int>> AL;
vector<bool> dest;
ll memo[400];

ll dp(int page) {
  if (AL[page].empty()) {
    return dest[page];
  }
  ll &ans = memo[page];
  if (ans != -1) return ans;
  ans = 0;
  for (int v : AL[page]) {
    ans += dp(v);
  }
  return ans;
}

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
  cin >> T;
  while (T--) {
    memset(memo, -1, sizeof memo);
    cin >> S;
    cin.ignore();
    AL.assign(400, {});
    dest.assign(400, false);
    for (int i = 0;  i < S; i++) {
      getline(cin, s);
      vector<string> t(split(s, ' '));
      if (t.size() == 2) {
        if (t[1] == "favourably") dest[stoi(t[0]) - 1] = true;
      } else {
        for (int j = 1; j < t.size(); j++) AL[stoi(t[0]) - 1].push_back(stoi(t[j]) - 1);
      }
    }
    cout << dp(0) << '\n';
  }
}