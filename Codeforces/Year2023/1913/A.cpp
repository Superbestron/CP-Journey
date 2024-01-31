#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;
typedef vector<ii> vii;
typedef vector<ll> vll;

int t;
string s;

void solve() {
  cin >> s;
  for (int i = 0; i < s.size() - 1; i++) {
    string first = s.substr(0, i + 1);
    string second = s.substr(i + 1);
    if (second[0] == '0') continue;
    if (stoi(first) < stoi(second)) {
      cout << first << ' ' << second << '\n';
      return;
    }
  }
  cout << -1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
