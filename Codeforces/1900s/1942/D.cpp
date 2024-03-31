#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

int t, n, k;

void solve() {
  cin >> n >> k;
  vector<vi> a(n, vi(n)), memo(n);
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    // idea is taking top k elems from i + 2 non-decreasing lists
    priority_queue<iii> pq;  // val, list_idx, idx

    // total i + 1 + 1 lists
    vector<vi*> lists;

    // iterate from all left_endpoint, take [l, i]
    for (int l = 0; l <= i; l++) {
      int before_l = l - 2;
      if (before_l >= 0) {
        lists.push_back(&memo[before_l]);
        pq.emplace(a[l][i] + memo[before_l][0], l, 0);
      } else {
        vi *temp = new vi(1);
        lists.push_back(temp);
        pq.emplace(a[l][i], l, 0);
      }
    }

    // don't take i at all
    if (i == 0) {
      vi *temp = new vi(1);
      lists.push_back(temp);
      pq.emplace(0, i + 1, 0);
    } else {
      lists.push_back(&memo[i - 1]);
      pq.emplace(memo[i - 1][0], i + 1, 0);
    }

    while (!pq.empty() && memo[i].size() < k) {
      auto [val, list_idx, idx] = pq.top(); pq.pop();
      memo[i].push_back(val);

      int sz = lists[list_idx]->size();
      idx++;
      if (idx == sz) continue;
      pq.emplace((*lists[list_idx])[idx] + ((list_idx - 2 >= 0 && list_idx <= i) ? a[list_idx][i] : 0), list_idx, idx);
    }
  }

  for (int i : memo[n - 1]) cout << i << ' ';
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
