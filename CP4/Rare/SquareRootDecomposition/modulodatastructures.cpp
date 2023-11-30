#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, Q, T, a, b, c, d;
  cin >> N >> Q;
  int sqrt_n = sqrt(N) + 1;
  vector<int> arr(N + 1);
  vector<vector<int>> bucket(sqrt_n + 1, vector<int>(sqrt_n));
  for (int i = 0; i < Q; i++) {
    cin >> T;
    if (T == 1) {
      cin >> a >> b >> c;
      if (b <= sqrt_n) bucket[b][a] += c;
      else {
        for (int j = a; j <= N; j += b) arr[j] += c;
      }
    } else {
      cin >> d;
      int sum_from_b = 0;
      for (int j = 1; j <= sqrt_n; j++) {
        sum_from_b += bucket[j][d % j];
      }
      cout << arr[d] + sum_from_b << '\n';
    }
  }
}
