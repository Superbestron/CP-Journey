#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int L, P;

void solve() {
  cin >> L >> P;
  vector<double> memo(L + P), prob(L + P);
  for (int i = 0; i < L; i++) {
    cin >> memo[i];
  }
  unordered_set<int> top;
  for (int i = 0; i < L + P; i++) {
    top.insert(i);
  }
  for (int i = L; i < L + P; i++) {
    double p_l, p_r; int l, r;
    cin >> p_l >> p_r >> l >> r;
    l--; r--;
    if (top.count(l)) top.erase(l);
    if (top.count(r)) top.erase(r);
    memo[i] = p_l * memo[l] + p_r * memo[r];
    prob[i] = 1 - p_l - p_r + p_l * prob[l] + p_r * prob[r];
  }
  double ans = -1;
  for (int i : top) {
    if (i < L) ans = max(ans, memo[i]);
    else ans = max(ans, memo[i] / (1 - prob[i]));
  }
  cout << setprecision(6) << fixed;
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
