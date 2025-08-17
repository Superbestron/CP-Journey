#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m, q;

inline void solve() {
  cin >> n >> m >> q;
  vi b(m), a(q);
  for (int &i : b) cin >> i;
  for (int &i : a) cin >> i;
  set<int> st;
  for (int i : b) {
    st.insert(i);
  }
  int lowest = *st.begin();
  int highest = *prev(st.end());
  for (int query : a) {
    if (query < lowest) {
      cout << lowest - 1 << '\n';
    } else if (query > highest) {
      int left = *prev(st.lower_bound(query));
      cout << n - left << '\n';
    } else {
      int left = *prev(st.lower_bound(query));
      int right = *st.lower_bound(query);
      if (query - left < right - query) {
        int temp = query - left - 1;
        cout << query - left - 1 + (right - temp - query + 1) / 2 << '\n';
      } else {
        int temp = right - query - 1;
        cout << right - query - 1 + (query - left + 1 - temp) / 2 << '\n';
      }
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
