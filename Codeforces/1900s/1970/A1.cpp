#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int, char> iii;
typedef vector<iii> viii;

int t, n;
string s;

inline void solve() {
  cin >> s;
  n = s.size();
  viii pref_balance;
  auto comp = [](const auto &a, const auto &b) {
    auto &[bal1, idx1, ch1] = a;
    auto &[bal2, idx2, ch2] = b;
    if (bal1 == bal2) return b < a;
    return bal1 < bal2;
  };
  int bal = 0;
  for (int i = 0; i < n; i++) {
    pref_balance.emplace_back(bal, i + 1, s[i]);
    if (s[i] == '(') bal++;
    else bal--;
  }
  sort(pref_balance.begin(), pref_balance.end(), comp);
  for (auto &[balance, idx, ch] : pref_balance) cout << ch;
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
//  cin >> t;
//  while (t--) {
    solve();
//  }
}
