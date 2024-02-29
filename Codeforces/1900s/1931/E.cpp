#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

int t, n, m;

int count_trailing_zeroes(int x) {
  int ans = 0;
  while (x % 10 == 0) {
    ans++;
    x /= 10;
  }
  return ans;
}

int digits(int x) {
  int ans = 0;
  while (x) {
    ans++;
    x /= 10;
  }
  return ans;
}

void solve() {
  cin >> n >> m;
  // at least m + 1 digits
  vi a(n), output;
  int sum = 0;
  for (int &i : a) {
    cin >> i;
    output.push_back(count_trailing_zeroes(i));
    sum += digits(i);
  }
  sort(output.begin(), output.end(), greater<>());
  for (int i = 0; i < output.size(); i += 2) {
    sum -= output[i];
  }
//  cout << sum << '\n';
  if (sum >= m + 1) cout << "Sasha\n";
  else cout << "Anna\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
