#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int max_N = 74, M;
  cin >> M;
  map<int, int> m;
  for (int i = 1; i <= max_N; i++) {
    int sum1 = i * i * i;
    for (int j = i; j <= max_N; j++) {
      int sum2 = j * j * j;
      int total = sum1 + sum2;
      if (total <= M) m[sum1 + sum2]++;
    }
  }
  for (auto it = m.rbegin(); it != m.rend(); it++) {
    if (it->second >= 2) {
      cout << it->first << '\n';
      return 0;
    }
  }
  cout << "none\n";
}
