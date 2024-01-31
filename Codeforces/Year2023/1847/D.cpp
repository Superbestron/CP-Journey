#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<int, int> ii;

int n, m, q, l, r, x;
string s;

void solve() {
  cin >> n >> m >> q >> s;
  set<int> st;
  vi pos(n, -1), indices;
  int one_cnt = 0;
  for (int i = 0; i < n; i++) {
    st.insert(i);
    if (s[i] == '1') one_cnt++;
  }
  for (int i = 0; i < m; i++) {
    cin >> l >> r;
    l--; r--;
    auto it = st.lower_bound(l);
    while (it != st.end() && *it <= r) {
      pos[*it] = indices.size();
      indices.push_back(*it);
      it = st.erase(it);
    }
  }

  int swaps = 0;
  for (int i = 0; i < min((int) indices.size(), one_cnt); i++) {
    if (s[indices[i]] == '0') swaps++;
  }

  for (int i = 0; i < q; i++) {
    cin >> x; x--;
    if (pos[x] != -1 && pos[x] + 1 <= one_cnt) {
      // a 1 has been swapped to this pos initially
      // now we don't need to
      if (s[x] == '0') swaps--;
      else swaps++;
    }
    if (s[x] == '0') {
      s[x] = '1';
      one_cnt++;
      // use this 1 to cover s[indices[one_cnt - 1]]
      if (one_cnt <= indices.size() && s[indices[one_cnt - 1]] == '0') swaps++;
    } else {
      s[x] = '0';
      // one less 1 to cover s[indices[one_cnt - 1]]
      if (one_cnt <= indices.size() && s[indices[one_cnt - 1]] == '0') swaps--;
      one_cnt--;
    }
    cout << swaps << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
