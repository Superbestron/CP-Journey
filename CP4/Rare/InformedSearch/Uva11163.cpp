#include <bits/stdc++.h>
using namespace std;

#define SIZE 40
#define MAX_MOVE_COUNT 100

// It's actually a modified 15-puzzle problem! Think about it carefully :)

int p[SIZE], king, lim, N, tc = 1, ROW_SIZE;
int dr[] = {0, -1, 0, 1}; // E,N,W,S
int dc[] = {1, 0, -1, 0}; // R,U,L,D
int pred[MAX_MOVE_COUNT + 1];

inline int h1() {
  int ans = 0;
  for (int r = 0; r < ROW_SIZE; r++) {
    for (int c = 0; c < 4; c++) {
      if (r * 4 + c == king) {  // we don't count that as part of the heuristic
        continue;
      } else {
        int tc = p[r * 4 + c] % 4, tr = p[r * 4 + c] / 4;
        ans += abs(tr - r) + (tc != c) + ((tc ^ c) == 2);
      }
    }
  }
  return ans;
}

inline int h2(int r, int c, int nr, int nc) {  // current blank position, new blank position
  int target = p[nr * 4 + nc];
  int tc = target % 4, tr = target / 4;
  return -(abs(tr - nr) + (tc != nc) + ((tc ^ nc) == 2)) +
      (abs(tr - r) + (tc != c) + ((tc ^ c) == 2));  // remove old piece, add new piece
}

bool DFS(int g, int h, int k) {  // current blank pos, cost of coming here, heuristic cost
  if (g + h > lim) return false;
  if (h == 0) return true;

  int r = k / 4, c = k % 4;
  for (int i = 0; i < 4; i++) {
    if (g != 0 && ((pred[g - 1] ^ 2) == i)) continue;  // dont kgo backwards
    int new_r = r + dr[i], new_c = c + dc[i];
    if (new_r < 0 || new_r >= ROW_SIZE) continue;
    new_c = (new_c + 4) % 4;  // wraparound
    int new_k = new_r * 4 + new_c;
    int delta = h2(r, c, new_r, new_c);
    swap(p[k], p[new_k]);
    pred[g] = i;
    if (DFS(new_k, g + 1, h + delta)) return true;
    swap(p[new_k], p[k]);
  }

  return false;
}

int IDA_Star() {
  lim = h1();
  while (lim <= MAX_MOVE_COUNT) { // pruning condition in the problem
    if (DFS(0, h1(), king))
      return lim;
    lim++;
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> N) {
    if (N == 0) break;
    ROW_SIZE = N / 4;
    for (int i = 0; i < N; i++) {
      cin >> p[i];
      if (p[i] == 1) king = i;
      p[i]--;
    }

    cout << "Set " << tc++ << ":\n" << IDA_Star() << '\n';
  }
}