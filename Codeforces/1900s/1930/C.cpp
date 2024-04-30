#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n;

auto comp = [](auto &a, auto &b) {
  auto &[x1, y1] = a;
  auto &[x2, y2] = b;
  if (x1 == y1) {
    return y1 > y2;
  }
  return x1 < x2;
};

void solve() {
  cin >> n;
  vll a(n);

  priority_queue<ii, vii, decltype(comp)> pq(comp);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    pq.emplace(a[i] + i + 1, i);
  }

  int cnt = 0, curr_val;
  while (!pq.empty()) {
    if (cnt == 0) {
      auto [top, top_idx] = pq.top(); pq.pop();
      curr_val = top;
      cnt++;
    }

    while (!pq.empty() && pq.top().first == curr_val) {
      cnt++;
      pq.pop();
    }

    cout << curr_val << ' ';
    curr_val--;
    cnt--;
  }

  while (cnt--) {
    cout << curr_val << ' ';
    curr_val--;
  }

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
