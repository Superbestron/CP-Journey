#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  vii a(3);
  for (auto &[x, y] : a) cin >> x >> y;
  if (a[0].first == a[1].first && a[1].first == a[2].first || a[0].second == a[1].second && a[1].second == a[2].second) {
    cout << 1 << '\n';
  } else if (a[0].first == a[1].first && (min(a[0].second, a[1].second) >= a[2].second || a[2].second >= max(a[0].second, a[1].second))
      || a[1].first == a[2].first && (min(a[2].second, a[1].second) >= a[0].second || a[0].second >= max(a[2].second, a[1].second))
      || a[0].first == a[2].first && (min(a[0].second, a[2].second) >= a[1].second || a[1].second >= max(a[0].second, a[2].second))
      || a[0].second == a[1].second && (min(a[0].first, a[1].first) >= a[2].first || a[2].first >= max(a[0].first, a[1].first))
      || a[1].second == a[2].second && (min(a[2].first, a[1].first) >= a[0].first || a[0].first >= max(a[2].first, a[1].first))
      || a[0].second == a[2].second && (min(a[0].first, a[2].first) >= a[1].first || a[1].first >= max(a[0].first, a[2].first))) {
    cout << 2 << '\n';
  } else cout << 3 << '\n';
}
