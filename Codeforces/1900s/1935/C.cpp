#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, l;

auto comp = [](ii &a, ii &b) {
  if (a.second == b.second) return a.first < b.first;
  return a.second < b.second;
};

void solve() {
  cin >> n >> l;
  vii A(n);
  for (auto &[a, b] : A) cin >> a >> b;
  sort(A.begin(), A.end(), comp);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    multiset<int> s;
    int cur = 0;
    for (int j = i; j < n; j++) {
      s.insert(A[j].first);
      cur += A[j].first;
      while (!s.empty() && A[j].second - A[i].second + cur > l) {
        int max_value = *s.rbegin();
        cur -= max_value;
        s.extract(max_value);
      }
      ans = max(ans, (int) s.size());
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
