#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T, N;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cin >> N;
    vii arr(N);
    double maxi = 1e9, mini = 0, a, b;
    for (int i = 0; i < N; i++) {
      cin >> a >> b;
      maxi = min(maxi, (i + 1) / a);
      mini = max(mini, (i + 1) / b);
    }
    printf("Case #%d: ", t);
    if (maxi >= mini) {
      cout << fixed << setprecision(6) << mini << '\n';
    } else {
      cout << -1 << '\n';
    }
  }
}
