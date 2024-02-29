#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

int t, n;
string s;

void solve() {
  cin >> n >> s;
  vector<int> prefix;
  prefix.push_back(0);
  for (int i = 0; i < n - 1; i++) {
    prefix.push_back(prefix.back() + (s[i] - '0'));
  }
  // do the multiplication
  ll carry = 0;
  vi output;
  for (int i = n - 1; i >= 0; i--) {
    ll sum = prefix[i] + (s[i] - '0') + carry;
    output.push_back(sum % 10);
    carry = sum / 10;
  }
  while (carry > 0) {
    output.push_back(carry % 10);
    carry /= 10;
  }
  while (output.back() == 0) output.pop_back();
  for (int i = output.size() - 1; i >= 0; i--) {
    cout << output[i];
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
