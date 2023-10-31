#include <bits/stdc++.h>
using namespace std;

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
  int n;
  string s;
  while (cin >> n && n != 0) {
    vector<int> v(n);
    int sum = 0, ans = 0;
    for (auto& i : v) {
      cin >> s;
      vector<string> str(split(s, '.'));
      i = stoi(str[0]) * 100 + stoi(str[1]);
      sum += i;
    }
    sort(v.begin(), v.end());
    int each = sum / n, extra = sum % n;
    // distribute the extra 1 cent to the richest ppl
    for (int i = n - 1; i >= 0; i--) {
      if (v[i] > each && extra) {
        ans--;
        extra--;
      }
      else if (each >= v[i]) break;
      ans += v[i] - each;
    }
    double final = ans;
    final /= 100;
    cout << '$' << fixed << setprecision(2) << final << '\n';
  }
}