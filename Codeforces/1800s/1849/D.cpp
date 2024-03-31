//#include <bits/stdc++.h>
//using namespace std;
//typedef long long ll;
//typedef vector<int> vi;
//typedef vector<ll> vll;
//typedef pair<int, int> ii;
//typedef vector<ii> vii;
//
//int t, n;
//vector<vector<vi>> memo;
//vi a;
//
//// blue == 0, red == 1
//int dp(int idx, int curr, int prev) {
//  if (idx == n) {
//    // paint the last one
//    if (curr == 0) return 1;
//    else return 0;
//  }
//  int &ans = memo[idx][curr][prev];
//  if (ans != -1) return ans;
//  ans = 1e9;
//  if (prev == 1) {
//    ans = min(ans, dp(idx + 1, 0, curr)); // don't paint red
//    if (a[idx] == 2) {
//      ans = min(ans, (curr == 0) ? 1 : 0 + dp(idx + 1, 1, curr)); // paint myself, next and prev red
//    } else if (a[idx] == 1) {
//      ans = min(ans, (curr == 0) ? 1 : 0 + dp(idx + 1, 1, curr)); // paint the next one red
//    }
//  } else {
//    if (a[idx] == 2) {
//      ans = min(ans, (curr == 0) ? 1 : 0 + dp(idx + 1, 1, curr)); // paint myself, next and prev red
//    } else if (a[idx] == 1) {
//      ans = min(ans, (curr == 0) ? 1 : 0 + dp(idx + 1, 0, curr)); // paint myself, prev red
//    }
//  }
//  return ans;
//}
//
//void solve() {
//  cin >> n;
//  a.assign(n, 0);
//  memo.assign(n, vector<vi>(2, vi(2, -1)));
//  for (int &i : a) cin >> i;
//  cout << dp(0, 0, 1) << '\n';
//}
//
//int main() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(nullptr);
////  cin >> t;
////  while (t--) {
//    solve();
////  }
//}
