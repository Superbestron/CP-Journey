#include <bits/stdc++.h>
using namespace std;

#define ROW_SIZE 4 // ROW_SIZE is a matrix of 4 x 4
#define PUZZLE (ROW_SIZE * ROW_SIZE)
#define X 15
#define MAX_MOVE_COUNT 45

int p[PUZZLE], blank, lim;
int dr[] = {0, -1, 0, 1}; // E,N,W,S
int dc[] = {1, 0, -1, 0}; // R,U,L,D
int pred[MAX_MOVE_COUNT + 1];
char ANS[] = "RULD";

inline int h1() { // heuristic: sum of Manhattan distances (compute all)
  int ans = 0;
  for (int i = 0; i < PUZZLE; i++) {
    if (p[i] != X)
      ans += abs(i / ROW_SIZE - p[i] / ROW_SIZE) + abs(i % ROW_SIZE - p[i] % ROW_SIZE); // Manhattan distance
  }
  return ans;
}

inline int h2(int i1, int j1, int i2, int j2) { // heuristic: sum of manhattan distances (compute delta)
  int tgt_i = p[i2 * ROW_SIZE + j2] / ROW_SIZE, tgt_j = p[i2 * ROW_SIZE + j2] % ROW_SIZE;
  return -(abs(i2 - tgt_i) + abs(j2 - tgt_j)) + (abs(i1 - tgt_i) + abs(j1 - tgt_j));
}

inline bool valid(int r, int c) {
  return 0 <= r && r < ROW_SIZE && 0 <= c && c < ROW_SIZE;
}

bool DFS(int g, int h, int k) {
  if (g + h > lim) return false;
  if (h == 0) return true;

  int i = k / ROW_SIZE, j = k % ROW_SIZE, d, new_i, new_j;

  for (d = 0; d < 4; d++) {
    // Prevent the blank from going back the same direction it came from
    if (g != 0 && d == (pred[g] ^ 2)) continue;
    new_i = i + dr[d];
    new_j = j + dc[d];
    if (valid(new_i, new_j)) {
      int new_k = new_i * ROW_SIZE + new_j;
      int dh = h2(i, j, new_i, new_j);
      swap(p[k], p[new_k]); // swap first
      pred[g + 1] = d;
      if (DFS(g + 1, h + dh, new_k)) // if ok, no need to restore, just go ahead
        return true;
      swap(p[k], p[new_k]); // restore
    }
  }

  return false;
}

int IDA_Star() {
  lim = h1();
  while (lim <= MAX_MOVE_COUNT) { // pruning condition in the problem
    if (DFS(0, h1(), blank))
      return lim;
    lim += 2;
  }
  return -1;
}

void output(int d) {
  if (d == 0) return;
  output(d - 1);
  cout << ANS[pred[d]];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  while (N--) {
    int i, j, sum = 0, ans;
    for (i = 0; i < PUZZLE; i++) {
      cin >> p[i];
      if (p[i] == 0) {
        p[i] = X; // change to X (15)
        blank = i; // remember the index
      } else p[i]--; // use 0-based indexing
    }

    for (i = 0; i < PUZZLE; i++)
      for (j = 0; j < i; j++)
        if (p[j] > p[i])
          sum++;
    sum += blank / ROW_SIZE + blank % ROW_SIZE;
    sum -= X / ROW_SIZE + X % ROW_SIZE;

    if (sum % 2 == 0 && ((ans = IDA_Star()) != -1)) {
      output(ans);
      cout << '\n';
    } else cout << "This puzzle is not solvable.\n";
  }
}
