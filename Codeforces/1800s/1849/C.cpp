#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int, int> iiii;

int t, n, m;
string s;

void solve() {
  cin >> n >> m >> s;
  vi b;
  vii c;
  set<iiii> st;
  b.push_back(0);
  char prev = '0';
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (prev == '1') {
      if (s[i] == '0') c.emplace_back(cnt, i - b.back()), b.push_back(i), cnt = 0;
    }
    prev = s[i];
    if (s[i] == '1') cnt++;
  }
  c.emplace_back(cnt, n - b.back());
  for (int i = 0; i < m; i++) {
    int l, r; cin >> l >> r;
    l--; r--;
    auto it = upper_bound(b.begin(), b.end(), l);
    it--;
    int l_range = it - b.begin();
    auto [cnt1, len1] = c[l_range];
    int actual_idx1 = b[l_range];
    cnt1 = min(cnt1, actual_idx1 + len1 - l);

    auto it2 = upper_bound(b.begin(), b.end(), r);
    it2--;
    int r_range = it2 - b.begin();
    auto [cnt2, len2] = c[r_range];
    int actual_idx2 = b[r_range];
    cnt2 = min(len2 - cnt2, r - actual_idx2 + 1);

    if (l_range == r_range) st.emplace(-1, -1, -1, -1);
    else st.emplace(l_range, r_range, cnt1, cnt2);
  }
  cout << st.size() << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}