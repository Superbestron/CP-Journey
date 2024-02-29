#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, k;
  cin >> n >> k;
  ll largest_n = 0, remain = 0, sum = 0;
  for (int i = n - 1; i >= 0; i--) {
    sum += i;
    if (sum > k) {
      largest_n = i + 1;
      remain = k - sum + i;
      break;
    }
  }
  vi ans(n);
  for (int i = 0, val = n - largest_n + 1; i < largest_n; i++, val++) {
    ans[i] = val;
  }
  for (int i = n - 1, val = 1; i >= largest_n; i--, val++) {
    ans[i] = val;
  }
  if (remain != 0) swap(ans[remain - 1], ans[remain]);
  for (int i : ans) cout << i << ' ';
  cout << '\n';
}
