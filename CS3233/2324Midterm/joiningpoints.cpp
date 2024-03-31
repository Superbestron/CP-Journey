#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
#define LLINF 4e18

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, u, v;
  cin >> n;
  ll min_x = LLINF;
  ll min_y = LLINF;
  ll max_x = -LLINF;
  ll max_y = -LLINF;
  vii pairs;
  for (int i = 0; i < n; i++) {
    cin >> u >> v;
    min_x = min(min_x, u);
    max_x = max(max_x, u);
    min_y = min(min_y, v);
    max_y = max(max_y, v);
    pairs.emplace_back(u, v);
  }

  int size = max(max_x - min_x, max_y - min_y);

  if (size == 0) {
    cout << max_x << ' ' << max_x + 1 << ' ' << max_y << ' ' << max_y + 1 << '\n';
    return 0;
  }

  ll xx = min_x;
  ll yy = min_y;
  ll aa = min_x + size;
  ll bb = min_y + size;
  bool can = true;
  for (int i = 0; i < n && can; i++) {
    if (pairs[i].first == xx || pairs[i].second == yy || pairs[i].first == aa || pairs[i].second == bb) {
    } else can = false;
  }

  if (can) {
    cout << xx << ' ' << aa << ' ' << yy << ' ' << bb << '\n';
    return 0;
  }

  xx = max_x - size;
  yy = max_y - size;
  aa = max_x;
  bb = max_y;
  can = true;

  for (int i = 0; i < n && can; i++) {
    if (pairs[i].first == xx || pairs[i].second == yy || pairs[i].first == aa || pairs[i].second == bb) {
      continue;
    } else can = false;
  }

  if (can) {
    cout << xx << ' ' << aa << ' ' << yy << ' ' << bb << '\n';
    return 0;
  }

  cout << "Impossible\n";
}
