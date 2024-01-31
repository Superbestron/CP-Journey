#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

// Knuth-Yao's DP optimisation
// Can refer to wikipedia for explanation

vector<vi> memo, opt;
vi prefix;
const int inf = 1e9;
int n;

inline int cost(int i, int j) {
  if (i > j) return 0;
  return prefix[j + 1] - prefix[i];
}

int dpKnuth(int i, int j) {
  if (i > j) return 0;
  if (i == j) {
    opt[i][j] = i;
    return memo[i][j] = cost(i, j);
  }
  if (memo[i][j] != -1) return memo[i][j];
  memo[i][j] = inf;

  int start = (j > i ? opt[i][j - 1] : i);
  if (start == -1) start = i;

  int end = (i < n - 1 ? opt[i + 1][j] : j);
  if (end == -1) end = j;

  for (int k = start; k <= end; k++) {
    int tcost = dpKnuth(i, k - 1) + dpKnuth(k + 1, j) + cost(i, j);
    if (tcost < memo[i][j]) {
      memo[i][j] = tcost;
      opt[i][j] = k;
    }
  }
  return memo[i][j];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> n) {
    memo.assign(n, vi(n, -1));
    opt.assign(n + 1, vi(n + 1, -1));
    prefix.clear();
    prefix.push_back(0);
    for (int i = 0; i < n; i++) {
      int val;
      cin >> val;
      prefix.push_back(prefix.back() + val);
    }
    cout << dpKnuth(0, n - 1) - cost(0, n - 1) << '\n';
  }
}
