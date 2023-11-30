#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t, n, q, x;

void solve() {
  cin >> n >> q;
  cout << 1 << ' ' << 2 << '\n';
  cout << 2 << ' ' << 3 << '\n';
  if (n == 3) {
    for (int i = 0; i < q; i++) {
      cin >> x;
      cout << "-1 -1 -1\n";
    }
    return;
  }
  deque<int> right, centre;
  centre.push_back(2);
  right.push_back(2);
  stack<int> temp;
  right.push_back(3);
  for (int i = 4; i <= n; i++) {
    if (i == 4) cout << 2 << ' ' << i << '\n';
    else cout << i - 1 << ' ' << i << '\n';
    centre.push_back(i);
  }
  for (int i = 0; i < q; i++) {
    cin >> x;
    if (x == right.size() || x == centre.size()) {
      cout << "-1 -1 -1\n";
    } else {
      int turns = abs(x - (int) right.size());
      if (x > right.size()) {
        int last;
        while (turns--) {
          last = centre.back();
          temp.push(centre.back()); centre.pop_back();
        }
        cout << last << ' ' << centre.back() << ' ' << right.back() << '\n';
        while (!temp.empty()) {
          right.push_back(temp.top()); temp.pop();
        }
      } else {
        int last;
        while (turns--) {
          last = right.back();
          temp.push(right.back()); right.pop_back();
        }
        cout << last << ' ' << right.back() << ' ' << centre.back() << '\n';
        while (!temp.empty()) {
          centre.push_back(temp.top()); temp.pop();
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
