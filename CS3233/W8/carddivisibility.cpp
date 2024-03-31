#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

ll L, R;

void solve() {
  cin >> L >> R;
  int modR = R % 9, modL = (L - 1) % 9;
  int sumR = 0, sumL = 0;
  for (int i = 1; i <= modR; i++) sumR += i;
  for (int i = 1; i <= modL; i++) sumL += i;
  cout << (45 + sumR - sumL) % 9 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
