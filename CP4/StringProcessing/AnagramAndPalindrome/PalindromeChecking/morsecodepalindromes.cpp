#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ll> vll;

string s, m;
unordered_map<char, string> mp = {
    {'A', "12"}, {'B', "2111"}, {'C', "2121"}, {'D', "211"}, {'E', "1"}, {'F', "1121"}, {'G', "221"}, {'H', "1111"},
    {'I', "11"}, {'J', "1222"}, {'K', "212"}, {'L', "1211"}, {'M', "22"}, {'N', "21"}, {'O', "222"}, {'P', "1221"},
    {'Q', "2212"}, {'R', "121"}, {'S', "111"}, {'T', "2"}, {'U', "112"}, {'V', "1112"}, {'W', "122"}, {'X', "2112"},
    {'Y', "2122"}, {'Z', "2211"}, {'0', "22222"}, {'1', "12222"}, {'2', "11222"}, {'3', "11122"}, {'4', "11112"},
    {'5', "11111"}, {'6', "21111"}, {'7', "22111"}, {'8', "22211"}, {'9', "22221"}
};

inline void solve() {
  getline(cin, s);
  int cnt = 0;
  for (char &c : s) {
    if (islower(c)) c = ::toupper(c);
    if (!mp.count(c)) continue;
    m += mp[c];
    cnt++;
  }
  if (cnt == 0) {
    cout << 0 << '\n';
    return;
  }
  int n = m.size();
  for (int i = 0; i < n / 2; i++) {
    if (m[i] != m[n - i - 1]) {
      cout << 0 << '\n';
      return;
    }
  }
  cout << 1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
