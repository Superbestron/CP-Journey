#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  string s;
  cin >> n >> m;
  vector<string> v(n);
  for (auto &s : v) cin >> s;
  vector<vector<vi>> DATs(n, vector<vi>(26));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < v[i].size(); j++) {
      DATs[i][v[i][j] - 'a'].push_back(j);
    }
  }
  for (int i = 0; i < m; i++) {
    cin >> s;
    bool print = false;
    for (int j = 0; j < n; j++) {
      int idx = -1, found = 0;
      for (int k = 0; k < 3; k++) {
        auto it = upper_bound(DATs[j][s[k] - 'A'].begin(), DATs[j][s[k] - 'A'].end(), idx);
        if (it == DATs[j][s[k] - 'A'].end()) {
          break;
        }
        idx = *it;
        found++;
      }
      if (found == 3) {
        cout << v[j] << '\n';
        print = true;
        break;
      }
    }
    if (!print) cout << "No valid word\n";
  }
}
