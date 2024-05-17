#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;
string s;

inline void solve() {
  cin >> n >> s;
  int ans = 0;
  for (int i = 0; i < n - 2; i++) {
    bool isMap = s[i] == 'm' && s[i + 1] == 'a' && s[i + 2] == 'p';
    bool isPie = s[i] == 'p' && s[i + 1] == 'i' && s[i + 2] == 'e';
    bool isMapie = i < n - 4 && s[i] == 'm' && s[i + 1] == 'a' && s[i + 2] == 'p' && s[i + 3] == 'i' && s[i + 4] == 'e';
    if (isMapie) {

    } else if (isMap) ans++;
    else if (isPie) ans++;
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
