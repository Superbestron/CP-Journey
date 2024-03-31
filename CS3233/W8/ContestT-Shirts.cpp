#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

int t, n;

void solve() {
  vi have(7), need(7);
  for (int &i : have) cin >> i;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    if (s == "XXXL") need[0]++;
    else if (s == "XXL") need[1]++;
    else if (s == "XL") need[2]++;
    else if (s == "L") need[3]++;
    else if (s == "M") need[4]++;
    else if (s == "S") need[5]++;
    else need[6]++;
  }
  bool allwell = true;
  for (int i = 0; i < 7; i++) {
    if (have[i] < need[i]) {
      allwell = false;
      break;
    }
  }
  if (allwell) cout << "ALL IS WELL\n";
  else {
    int curr = have[0];
    bool accep = true;
    for (int i = 0; i < 7; i++) {
      if (i != 6) curr += have[i + 1];
      if (curr < need[i]) {
        accep = false; break;
      }
      curr -= need[i];
      curr = min(curr, (i != 6 ? have[i + 1] : 0) + have[i]);
    }
    if (accep) cout << "still acceptable\n";
    else cout << "argh... :(\n";
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
