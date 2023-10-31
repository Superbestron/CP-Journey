#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

vector<int> memo(1e6 + 1, -1);

int factorial(int num) {
  if (num <= 1) return 1;
  return num * factorial(num - 1);
}

// express num as 5a + b
int dp(int num) {
  if (num < 5) return factorial(num);
  int& ans = memo[num];
  if (ans != -1) return ans;
  int b = num % 5;
  int a = num / 5;
  int sum;
  int two_pow = a % 4;
  if (two_pow == 1) sum = 2;
  else if (two_pow == 2) sum = 4;
  else if (two_pow == 3) sum = 8;
  else sum = 6;
  return ans = (sum * dp(a) * dp(b)) % 10;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  while (cin >> n && n != 0) {
    cout << dp(n) << '\n';
  }
}