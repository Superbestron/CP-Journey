#include <bits/stdc++.h>
using namespace std;

unordered_set<int> s;
int memo[1000001];

bool dp(int x) {
  if (x == 0) return false;
  int &ans = memo[x];
  if (ans != -1) return ans;
  ans = 0;
  for (int i : s) {
    if ((x - i) < 0) continue;
    ans |= !dp(x - i);
    if (ans) break;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, v;
  while (cin >> n >> m) {
    memset(memo, -1, sizeof memo);
    s.clear();
    for (int i = 0; i < m; i++) {
      cin >> v;
      s.insert(v);
    }
    if (dp(n)) cout << "Stan wins\n";
    else cout << "Ollie wins\n";
  }
}
