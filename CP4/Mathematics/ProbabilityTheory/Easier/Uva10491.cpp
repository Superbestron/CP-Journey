#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  double NCOWS, NCARS, NSHOW;
  while (cin >> NCOWS >> NCARS >> NSHOW) {
    double ans1 = (NCOWS / (NCOWS + NCARS)) * (NCARS / (NCARS + NCOWS - NSHOW - 1));
    double ans2 = (NCARS / (NCOWS + NCARS)) * ((NCARS - 1) / (NCARS + NCOWS - NSHOW - 1));
    cout << setprecision(5) << fixed << ans1 + ans2 << '\n';
  }
}
