#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;

int t, n;
string s;

vector<string> split(string &s, char delimiter) {
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

void solve() {
  cin >> s;
  vector<string> l_r = split(s, '=');
  string right = l_r[1];
  map<char, int> mp;
  for (char c : right) {
    if (!mp.count(c)) mp[c] = mp.size();
  }
  vi ans;
  vector<string> left = split(l_r[0], '+');
  for (auto &str : left) {
    for (char c : str) {
      if (!mp.count(c)) mp[c] = mp.size();
    }
  }
  int ctr = 0, count = 0;
  for (auto &[ch, idx] : mp) idx = ctr++;
  vi a(10);
  for (int i = 0; i < 10; i++) {
    a[i] = i;
  }
  do {
    bool can = true;
    ll sum_left = 0;
    for (auto str : left) {
      for (char &c : str) {
        c = (a[mp[c]] + '0');  // convert to integer
      }
      if (str[0] == '0') {
        can = false;
        break;
      }
      sum_left += stoi(str);
    }
    if (!can) continue;
    string copy = right;
    for (char &c : copy) {
      c = (a[mp[c]] + '0');
    }
    if (copy[0] == '0') {
      can = false;
    }
    if (!can) continue;
    ll sum_right = stoi(copy);
    if (sum_left == sum_right) {
      count++;
      if (ans.empty()) ans = a;
    }
    if (count == 2) break;
    sort(a.begin() + mp.size(), a.end(), greater<>());
  } while (next_permutation(a.begin(), a.end()));
  if (count == 0) {
    cout << "impossible\n"; return;
  }
  for (int i = 0; i < left.size(); i++) {
    auto &str = left[i];
    for (char &c : str) {
      c = (ans[mp[c]] + '0');  // convert to integer
    }
    cout << str;
    if (i < left.size() - 1) cout << '+';
  }
  cout << '=';
  for (char &c : right) {
    c = (ans[mp[c]] + '0');
  }
  cout << right;
  if (count == 1) cout << '*';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
