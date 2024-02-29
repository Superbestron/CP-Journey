#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int N, M, K, post, book, price;
vector<vi> memo;
vector<unordered_map<int, int>> AL;
vi postage;

int dp(int idx, int bm) {
  if (idx == N) return 0;
  int &ans = memo[idx][bm];
  if (ans != -1) return ans;
  ans = 1e9;
  for (int i = 0; i < M; i++) {
    if (!AL[i].count(idx)) continue;
    int cost = AL[i][idx];
    // not used previously
    if ((bm & (1 << i)) == 0) {
      ans = min(ans, postage[i] + cost + dp(idx + 1, bm | (1 << i)));
    } else {
      ans = min(ans, cost + dp(idx + 1, bm));
    }
  }
  return ans;
}

void solve() {
  cin >> N >> M;
  memo.assign(N, vi((1 << M) + 1, -1));
  AL.assign(M, {});
  for (int i = 0; i < M; i++) {
    cin >> K >> post;
    postage.push_back(post);
    for (int j = 0; j < K; j++) {
      cin >> book >> price;
      book--;
      AL[i][book] = price;
    }
  }
  cout << dp(0, 0) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
