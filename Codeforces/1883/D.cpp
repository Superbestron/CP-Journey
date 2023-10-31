#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, l, r;
  char c;
  multiset<int> start, end;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> c >> l >> r;
    if (c == '+') {
      start.insert(l);
      end.insert(r);
    } else {
      start.erase(start.find(l));
      end.erase(end.find(r));
    }
    if (!start.empty() && start.upper_bound(*end.begin()) != start.end()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}