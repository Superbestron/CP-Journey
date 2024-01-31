#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, a, b;
  cin >> N;
  vi array(43 * 24 + 50);
  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    array[a / 3600]++;
    array[(a + b - 1) / 3600 + 1]--;
  }
  int ans = 0, idx = 0, sum = 0;
  for (int i = 0; i < 43 * 24; i++) {
    sum += array[i];
    if (sum > ans) {
      ans = sum;
      idx = i;
    }
  }
  cout << ans << '\n';
  cout << "day " << idx / 24 << " hour " << (((idx + 1) % 24) == 0 ? 24 : (idx + 1) % 24) << '\n';
}
