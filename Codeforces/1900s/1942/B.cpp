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
  vi a(n), output;
  set<int> st;
  st.insert(n);
  for (int &i : a) cin >> i;
  for (int i = n - 1; i >= 0; i--) {
    int mex = *st.begin();
    output.push_back(mex - a[i]);
    st.insert(mex - a[i]);
  }
  for (int i = n - 1; i >= 0; i--) cout << output[i] << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
