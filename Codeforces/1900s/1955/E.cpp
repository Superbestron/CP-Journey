#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;
string s;

void solve() {
  cin >> n >> s;
  vi ori(n + 1);
  for (int i = 0; i < n; i++) {
    ori[i] = (s[i] == '0');
  }
  for (int i = n; i >= 1; i--) {
    vi diff(n + 1);
    int sum = 0;
    for (int j = 0; j < n - i + 1; j++) {
      sum += diff[j];
      if ((sum + ori[j]) % 2 == 0) continue;
      diff[j + 1]++;
      diff[j + i]--;
    }
    bool can = true;
    for (int j = n - i + 1; j < n; j++) {
      sum += diff[j];
      if ((sum + ori[j]) % 2) can = false;
    }
    if (can) {
      cout << i << '\n';
      return;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
