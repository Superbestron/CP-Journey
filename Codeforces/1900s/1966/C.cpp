#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a;
  unordered_set<int> st;
  for (int i = 0; i < n; i++) {
    int v; cin >> v;
    if (st.count(v)) continue;
    st.insert(v);
    a.push_back(v);
  }
  sort(a.begin(), a.end());
  int idx = a.size();
  if (a[0] > 1) {
    cout << "Alice\n";
    return;
  }
  for (int i = 1; i < a.size(); i++) {
    if (a[i] - a[i - 1] > 1) {
      idx = i;
      break;
    }
  }
  if (idx == a.size()) {
    if (idx % 2 == 1) cout << "Alice\n";
    else cout << "Bob\n";
    return;
  }
  bool alice = idx % 2 == 0;
  if (alice) cout << "Alice\n";
  else cout << "Bob\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
