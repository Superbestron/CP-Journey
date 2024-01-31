#include <bits/stdc++.h>
using namespace std;

typedef tuple<int, int> ii;
typedef vector<int> vi;

int getNimSum(vi &pile) {
  int nim = 0;
  for (auto &p : pile)
    nim ^= p;
  return nim;
}

bool whoWinNimGame(vi &pile) {
  return getNimSum(pile) != 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  while (cin >> n) {
    if (n == 0) break;
    vi pile(n);
    for (int &i : pile) cin >> i;
    if (whoWinNimGame(pile)) cout << "Yes\n";
    else cout << "No\n";
  }
}
