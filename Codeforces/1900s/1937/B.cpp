#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;
string s1, s2;

void solve() {
  cin >> n >> s1 >> s2;
  int pos = 1;
  for (int i = 1; i < n; i++) {
    if (s1[i] == s2[i - 1]) {
      pos++;
    } else {
      if (s1[i] == '1') break;
      pos = 1;
      s2[i - 1] = s1[i];
    }
  }
  cout << s1[0] << s2 << '\n';
  cout << pos << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
