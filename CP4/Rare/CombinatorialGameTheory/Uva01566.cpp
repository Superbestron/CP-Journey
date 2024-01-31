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

bool whoWinMisereNimGame(vi &pile) {
  int n_more = 0, n_one = 0;
  for (int i : pile) {
    if (i > 1) n_more++;
    if (i == 1) n_one++;
  }
  if (n_more >= 1) return whoWinNimGame(pile);
  else return n_one % 2 == 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vi pile(n);
    for (int &i : pile) cin >> i;
    if (whoWinMisereNimGame(pile)) cout << "John\n";
    else cout << "Brother\n";
  }
}
