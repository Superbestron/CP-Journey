#include <bits/stdc++.h>
using namespace std;

char grid[2000][2000];
int memo[2000][2000][4][2];
// N -> 3, E -> 0, S -> 1, W -> 2
int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int n, c, r;

// Honestly, I think my direction switching bitmask technique is pretty clean

int dp(int x, int y, int dir, bool used) {
  if (x == r && y == n) return true;
  if (x < 0 || x >= n || y < 0 || y >= n) return false;
  int &ans = memo[x][y][dir][used];
  if (ans != -1) return ans;
  ans = 0;
  // N <-> W, S <-> E
  int new_dir = dir ^ 1;
  int new_x = x + directions[new_dir][0];
  int new_y = y + directions[new_dir][1];
  if (grid[x][y] == '\\') ans |= dp(new_x, new_y, new_dir, used);
  else if (grid[x][y] == '.' && !used) ans |= dp(new_x, new_y, new_dir, true);

  // N <-> E, S <-> W
  new_dir = dir ^ 3;
  new_x = x + directions[new_dir][0];
  new_y = y + directions[new_dir][1];
  if (grid[x][y] == '/') ans |= dp(new_x, new_y, new_dir, used);
  else if (grid[x][y] == '.' && !used) ans |= dp(new_x, new_y, new_dir, true);

  if (grid[x][y] == '.') {
    new_x = x + directions[dir][0];
    new_y = y + directions[dir][1];
    ans |= dp(new_x, new_y, dir, used);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> c >> r;
  c--; r--;
  memset(memo, -1, sizeof memo);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> grid[i][j];
  }
  if (dp(0, c, 1, 0)) cout << "YES\n";
  else cout << "NO\n";
}
