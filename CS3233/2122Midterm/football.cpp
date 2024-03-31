#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n, m, x;
vector<pair<unordered_set<int>, unordered_set<int>>> a;

bool merge(vi &v, int depth) {
  if (v.size() <= 1) return true;
  if (depth == m) return false;
  vi left, right;
  for (int i : v) {
    if (a[depth].first.count(i)) {
      left.push_back(i);
    } else {
      right.push_back(i);
    }
  }
  return merge(left, depth + 1) && merge(right, depth + 1);
}

void solve() {
  cin >> n >> m;
  if (n == 2) {
    cout << "YES\n";
    return;
  }
  a.assign(m, {unordered_set<int>(), unordered_set<int>()});
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> x;
      if (j >= n / 2) a[i].second.insert(x);
      else a[i].first.insert(x);
    }
  }
  vi v;
  for (int i = 0; i < n; i++) v.push_back(i + 1);
  if (merge(v, 0)) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
