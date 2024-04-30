#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

vll getDivisors(ll n) {
  vll ans;
  for (int i = 1; i <= sqrt(n); i++) {
    if (n % i == 0) {
      if (n / i == i) ans.push_back(i);
      else {
        ans.push_back(i);
        ans.push_back(n / i);
      }
    }
  }
  sort(ans.begin(), ans.end());
  return ans;
}

int main() {
  int n; cin >> n;
  vi a(n);
  for (int &i : a) cin >> i;
  int gcd_val = a[1] - a[0];
  for (int i = 2; i < n; i++) {
    gcd_val = gcd(gcd_val, a[i] - a[i - 1]);
  }
  vll output = getDivisors(gcd_val);
  for (int i = 1; i < output.size(); i++) cout << output[i] << ' ';
  cout << '\n';
}
