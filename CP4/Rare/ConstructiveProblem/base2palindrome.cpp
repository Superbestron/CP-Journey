#include <bits/stdc++.h>
using namespace std;

inline int binaryToDecimal(string &num) {
  int dec_value = 0;
  int base = 1;
  int len = num.length();
  for (int i = len - 1; i >= 0; i--) {
    if (num[i] == '1') dec_value += base;
    base <<= 1;
  }
  return dec_value;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int M; cin >> M;
  vector<vector<string>> v(2);
  set<int> s;
  s.insert(1); s.insert(3);
  v[0] = {"0", "1"};
  v[1] = {"00", "11"};
  for (int i = 2; i < 31; i++) {
    auto &last = v[i - 2];
    // generate all palindromes using (n - 2) length palindromes
    vector<string> temp;
    for (auto &str : last) {
      string s1 = "1";
      s1 += str;
      s1 += "1";
      s.insert(binaryToDecimal(s1));
      string s2 = "0";
      s2 += str;
      s2 += "0";
      temp.push_back(std::move(s1));
      temp.push_back(std::move(s2));
    }
    v.push_back(std::move(temp));
  }
  vector<int> ans(s.begin(), s.end());
  cout << ans[M - 1] << '\n';
}
