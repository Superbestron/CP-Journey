#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int C, S, val, tc = 1;
  while (cin >> C >> S) {
    vector<int> v;
    vector<pair<int, int>> ans;
    double AM = 0;
    for (int i = 0; i < S; i++) {
      cin >> val;
      v.push_back(val);
      AM += val;
    }
    for (int i = v.size(); i < 2 * C; i++) v.push_back(0);
    sort(v.begin(), v.end());
    AM /= C;
    double IM = 0;
    printf("Set #%d\n", tc++);
    for (int i = 0; i < C; i++) {
      int a = v[i], b = v[2 * C - i - 1];
      ans.emplace_back(a, b);
      IM += (fabs(AM - (a + b)));
      printf(" %d:", i);
      if (a != 0) printf(" %d", a);
      if (b != 0) printf(" %d", b);
      printf("\n");
    }
    printf("IMBALANCE = %.5lf\n\n", IM);
  }
}
