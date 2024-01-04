#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;

vi A;
vector<vll> memo;
vector<vector<vector<ii>>> output;

ll dp(int i, int j) {
  if (i == j) return 0;
  ll &ans = memo[i][j];
  if (ans != -1) return ans;

  ans = 1e9;
  for (int k = i; k < j; k++) {
    ll temp = dp(i, k) + dp(k + 1, j) + A[i] * A[k + 1] * A[j + 1];
    if (ans > temp) {
      ans = temp;
      output[i][j] = {{i, k}, {k + 1, j}};
    }
  }
  return ans;
}

string print(int i, int j) {
  if (i == j) return "A" + to_string(i + 1);
  auto &first = output[i][j][0];
  auto &second = output[i][j][1];
  string s1 = print(first.first, first.second);
  string s2 = print(second.first, second.second);
  return "(" + s1 + " x " + s2 + ")";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, tc = 1;
  while (cin >> N) {
    if (N == 0) break;
    A.assign(N + 1, 0);
    memo.assign(N, vll(N, -1));
    output.assign(N, vector<vector<ii>>(N));
    for (int i = 0; i < N; i++) {
      cin >> A[i] >> A[i + 1];
    }
    dp(0, N - 1);
    cout << "Case " << tc++ << ": " << print(0, N - 1) << '\n';
  }
}
