#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<int, int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
#define LSOne(S) ((S) & -(S))                    // the key operation

int t, n, l, r;

void solve() {
  cin >> n >> l >> r;
  vi a(n);
  unordered_set<int> midterm_ncovered; // not covered
  unordered_set<int> midterms;
  for (int &i : a) {
    cin >> i;
    midterm_ncovered.insert(i);
    midterms.insert(i);
  }
  sort(a.begin(), a.end());

  int ans = 0;
  for (int midterm : a) {
    if (!midterm_ncovered.count(midterm)) continue;
    int party = midterm - l;
    bool can = false;
    while (party >= 0 && party + r >= midterm) {
      if (!midterms.count(party)) {
        midterm_ncovered.erase(midterm);
        ans++;
        can = true;
        break;
      }
      party--;
    }
    if (!can) {
      cout << -1 << '\n';
      return;
    }
    for (int time = party + l; time <= party + r; time++) {
      if (midterm_ncovered.count(time)) midterm_ncovered.erase(time);
    }
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
