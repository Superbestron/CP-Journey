#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>                         // pbds
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ost;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int> ii;
typedef vector<ii> vii;

int t, n;

void solve() {
  cin >> n;
  vi a, b;
  vii idxes;
  for (int i = 0; i < n; i++) {
    int ai, bi; cin >> ai >> bi;
    idxes.emplace_back(ai, bi);
  }
  auto comp = [](ii &a, ii &b) {
    auto &[l1, r1] = a;
    auto &[l2, r2] = b;
    return r1 < r2;
  };
  sort(idxes.begin(), idxes.end(), comp);

  ll cnt = 0;
  ost st;
  for (int i = 0; i < n; i++) {
    auto &[ai, bi] = idxes[i];
    cnt += st.size() - st.order_of_key(ai);
    st.insert(ai);
  }
  cout << cnt << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
