#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, a, b;
  char op;
  bool firsty = true;
  while (cin >> n) {
    if (n == 0) break;
    if (firsty) firsty = false;
    else cout << '\n';
    vector<string> ans;
    int mx = 0;
    for (int i = 0; i < n; i++) {
      cin >> a >> op >> b;
      if (op == '+') ans.push_back(to_string(a + b));
      else if (op == '-') ans.push_back(to_string(a - b));
      else ans.push_back(to_string(a * b));
      mx = max(mx, (int) ans.back().size());
    }
    int mx_nums = 51 / (mx + 1), idx = 0;
    while (idx < n) {
      bool first = true;
      for (int i = 0; i < mx_nums && idx < n; i++, idx++) {
        if (first) first = false;
        else cout << ' ';
        for (int j = 0; j < mx - ans[idx].size(); j++) cout << ' ';
        cout << ans[idx];
      }
      cout << '\n';
    }
  }
}
