#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int t;
string s;

void solve() {
  cin >> s;
  int st = -1, idx = -1;
  stack<int> unst;
  unst.push(-1);
  for (char i : s) {
    if (i == '+') {
      idx++;
    } else if (i == '-') {
      idx--;
      st = min(st, idx);
      while (unst.top() > idx) unst.pop();
    } else if (i == '1') {
      if (unst.size() > 1) {
        cout << "NO\n";
        return;
      }
      st = idx;
    } else {
      if (idx < 1 || idx == st) {
        cout << "NO\n";
        return;
      }
      unst.push(idx);
    }
  }
  cout << "YES\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
