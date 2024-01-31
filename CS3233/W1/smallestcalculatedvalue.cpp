#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
vi v(3);
const int INF = 1e9 + 1;

int backtrack(int idx, int sum) {
  if (idx == 3) return sum;
  int ans = INF, temp;
  temp = backtrack(idx + 1, sum + v[idx]);
  ans = min(ans, temp < 0 ? INF : temp);
  temp = backtrack(idx + 1, sum - v[idx]);
  ans = min(ans, temp < 0 ? INF : temp);
  temp = backtrack(idx + 1, sum * v[idx]);
  ans = min(ans, temp < 0 ? INF : temp);
  if (v[idx] != 0 && sum % v[idx] == 0) {
    temp = backtrack(idx + 1, sum / v[idx]);
    ans = min(ans, temp < 0 ? INF : temp);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  for (int &i : v) cin >> i;
  cout << backtrack(1, v[0]) << '\n';
}
