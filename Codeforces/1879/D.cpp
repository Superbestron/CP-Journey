#include <bits/stdc++.h>

using namespace std;

const int N = 300005;
const int MOD = 998244353;
int n;
int arr[N];

void add(int &a, int b) {
  a += b;
  if (a >= MOD)
    a -= MOD;
}

int sum(int a, int b) {
  a += b;
  if (a >= MOD)
    a -= MOD;
  if (a < 0)
    a += MOD;
  return a;
}

int mul(int a, int b) {
  return (a * 1LL * b) % MOD;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];

  int res = 0;
  for (int b = 0; b < 30; ++b) {
    int cur = 0;
    vector <int> cnt(2);
    vector <int> sumOfL(2);
    cnt[0] = 1;
    int x = 0;
    for (int i = 0; i < n; ++i) {
      x ^= ((arr[i] >> b) & 1);
      int sumOfR = mul(cnt[x ^ 1], i + 1);
      add(cur, sum(sumOfR, -sumOfL[x ^ 1]));

      ++cnt[x];
      add(sumOfL[x], i + 1);
    }

    add(res, mul(1 << b, cur));
  }

  cout << res << endl;
}