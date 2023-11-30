#include <bits/stdc++.h>
using namespace std;

int main() {
  int num;
  unordered_map<int, pair<int, int>> m;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> num;
      m[num] = {i, j};
    }
  }
  double dist = 0;
  for (int i = 1; i < 9; i++) {
    auto &[x1, y1] = m[i];
    auto &[x2, y2] = m[i + 1];
    dist += hypot(x2 - x1, y2 - y1);
  }
  cout << setprecision(6) << fixed << dist << '\n';
}
