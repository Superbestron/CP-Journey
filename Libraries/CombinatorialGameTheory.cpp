#include <bits/stdc++.h>
using namespace std;

typedef tuple<int, int> ii;
typedef vector<int> vi;

bool isOn(int bit, int k) {  // is the k^th bit 1?
  return bit & (1 << k);
}

int getNimSum(vi &pile) {
  int nim = 0;
  for (auto &p : pile)
    nim ^= p;
  return nim;
}

// Returns true if first player wins
bool whoWinNimGame(vi &pile) {
  return getNimSum(pile) != 0;
}

ii winningMove(vi &pile) {
  int nimsum = getNimSum(pile);
  if (nimsum == 0) return {-1, -1};  // not winnable
  int pos = -1, remove = -1, d = 0;
  for (int i = 0; i < 31; i++) { // using signed 32-bit int
    if (isOn(nimsum, i)) d = i;
  }
  for (int i = 0; i < pile.size() && pos == -1; i++) {
    if (isOn(pile[i], d)) {
      pos = i;
      remove = pile[i] - (pile[i] ^ nimsum);
    }
  }
  return {pos, remove};
}

// Returns true if first player wins
bool whoWinMisereNimGame(vi &pile) {
  int n_more = 0, n_one = 0;
  for (int i : pile) {
    if (i > 1) n_more++;
    if (i == 1) n_one++;
  }
  if (n_more >= 1) return whoWinNimGame(pile);
  else return n_one % 2 == 0;
}

// Variation of Nim where each player can only remove at least half the number of stones from each pile

int getAtLeastHalfNimGrundy(int stone) {
  if (stone == 0) return 0;
  set<int> used;
  for (int take = (stone + 1) / 2; take <= stone; take++) {
    used.insert(getAtLeastHalfNimGrundy(stone - take));
  }
  int res = 0;
  while (used.count(res)) res++;
  return res;
}

bool whoWinAtLeastHalfNimGame(vi &pile) {
  vi grundy(pile.size());
  for (int i = 0; i < pile.size(); i++) {
    grundy[i] = getAtLeastHalfNimGrundy(pile[i]);
  }
  return getNimSum(grundy) != 0;
}
