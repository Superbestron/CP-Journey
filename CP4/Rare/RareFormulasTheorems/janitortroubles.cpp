#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int s1, s2, s3, s4;
  cin >> s1 >> s2 >> s3 >> s4;
  double s = (s1 + s2 + s3 + s4) / 2.0;
  // largest quadrilateral is a cyclic quadrilateral
  cout << setprecision(6) << fixed << sqrt((s - s1) * (s - s2)) * sqrt((s - s3) * (s - s4));
}
