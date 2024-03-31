#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

// Edit/Levenshtein Distance
// Commented out is space-saving technique, but string cannot be reconstructed
// If there are at most d insertions/deletions, we only need to consider cells within a diagonal
// band of width 2d + 1.
// Thus, for m, we only need to traverse from [max(1, i - d), min(n, i + d)], which runs in O(nd).
// Initialise the memo table to be -1e9, except on line 19.

const auto score = [](char a, char b) {
  return a == b ? 2 : -1;
};

int main() {
  string A("AGGGCT"), B("AGGCA");
  int n = A.size(), m = B.size();
  vector<vi> memo(n + 1, vi(m + 1));
  // vector<vi> memo(2, vi(m + 1));

  // insert/delete = -1 point
  for (int i = 1; i <= n; i++) memo[i][0] = i * -1;
  for (int j = 1; j <= m; j++) memo[0][j] = j * -1;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      // match = 2 points, mismatch = -1 point
      memo[i][j] = memo[i - 1][j - 1] + score(A[i - 1], B[j - 1]); // cost for match or mismatches
      // insert/delete = -1 point
      memo[i][j] = max(memo[i][j], memo[i - 1][j] + score(A[i - 1], '_')); // delete
      memo[i][j] = max(memo[i][j], memo[i][j - 1] + score('_', B[j - 1])); // insert
    }
  }
//  for (int i = 1; i <= n; i++) {
//    memo[i & 1][0] = i * -1;
//    for (int j = 1; j <= m; j++) {
//      // match = 2 points, mismatch = -1 point
//      memo[i & 1][j] = memo[(i - 1) & 1][j - 1] + score(A[i - 1], B[j - 1]); // cost for match or mismatches
//      // insert/delete = -1 point
//      memo[i & 1][j] = max(memo[i & 1][j], memo[(i - 1) & 1][j] score(A[i - 1], '_')); // delete
//      memo[i & 1][j] = max(memo[i & 1][j], memo[i & 1][j - 1] + score('_', B[j - 1])); // insert
//    }
//  }

  string A_C, B_C;
  auto reconstruct = [&](auto &&f, int i, int j) -> void { // NOLINT(misc-no-recursion)
    if (i == 0) {
      while (j) {
        A_C += '_';
        B_C += B[j - 1];
        j--;
      }
      return;
    }

    if (j == 0) {
      while (i) {
        A_C += A[i - 1];
        B_C += '_';
        i--;
      }
      return;
    }

    if (memo[i][j] - score(A[i - 1], B[j - 1]) == memo[i - 1][j - 1]) {
      if (A[i - 1] != B[j - 1]) {
        A_C += ']'; B_C += ']';
      }
      A_C += A[i - 1];
      B_C += B[j - 1];
      if (A[i - 1] != B[j - 1]) {
        A_C += '['; B_C += '[';
      }
      return f(f, i - 1, j - 1);
    }

    if (memo[i][j] - score(A[i - 1], '_') == memo[i - 1][j]) {
      A_C += A[i - 1];
      B_C += '_';
      return f(f, i - 1, j);
    }

    if (memo[i][j] - score('_', B[j - 1]) == memo[i][j - 1]) {
      A_C += '_';
      B_C += B[j - 1];
      return f(f, i, j - 1);
    }
  };

  reconstruct(reconstruct, n, m);
  reverse(A_C.begin(), A_C.end());
  reverse(B_C.begin(), B_C.end());

  cout << "Reconstructed strings:\n";
  cout << A_C << '\n' << B_C << "\n\n";

  cout << "DP table:\n";
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) cout << memo[i][j] << ' ';
    cout << '\n';
  }
  cout << "Maximmum Alignment Score: " << memo[n][m] << '\n';
  // cout << memo[n & 1][m] << '\n';
}
