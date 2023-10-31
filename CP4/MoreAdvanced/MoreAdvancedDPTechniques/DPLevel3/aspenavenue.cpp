#include <bits/stdc++.h>

using namespace std;

vector<int> v;
vector<vector<double>> memo;
vector<double> positions;
int N, L, W;

double dp(int left, int right) {
  if (left + right == N) return 0;
  double& ans = memo[left][right];
  if (ans > -0.5) return ans;
  ans = 1e9;
  int treeNo = left + right;
  if (left < N / 2) {
    double dist = abs(v[treeNo] - positions[left]);
    ans = min(ans, dp(left + 1, right) + dist);
  }
  if (right < N / 2) {
    double dist = sqrt((v[treeNo] - positions[right]) * (v[treeNo] - positions[right]) + W * W);
    ans = min(ans, dp(left, right + 1) + dist);
  }
  return memo[left][right] = ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> N >> L >> W) {
    v.assign(N, 0);
    double spacing = L / ((double) (N - 2) / 2);
    memo.assign(N / 2 + 1, vector<double>(N / 2 + 1, -1));
    positions.assign(N / 2, 0);
    for (int &i : v) cin >> i;
    sort(v.begin(), v.end());
    for (int i = 1; i < N / 2; i++) {
      positions[i] = positions[i - 1] + spacing;
    }
    cout << std::fixed << setprecision(6) << dp(0, 0) << '\n';
  }
}