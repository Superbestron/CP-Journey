#include <bits/stdc++.h>
using namespace std;

vector<int> v;
int N, m, k;

bool can(int cap) {
  int idx = 0;
  for (int i = 0; i < k; i++) {
    int sum = 0;
    while (idx < m && sum + v[idx] <= cap) {
      sum += v[idx];
      idx++;
    }
  }
  return idx == m;
}

int main() {
  cin >> N;
  for (int tc = 0; tc < N; tc++) {
    cin >> m >> k;
    v.assign(m, 0);
    for (int &i : v) cin >> i;
    int lo = 1, hi = 1e9;
    while (hi > lo) {
        int mid = (lo + hi) / 2;
        can(mid) ? hi = mid : lo = mid + 1;
    }
    int idx = m - 1;
    vector<vector<int>> ans;
    for (int i = 0; i < k; i++) {
      int sum = 0;
      vector<int> t;

      while (sum + v[idx] <= lo && idx >= k - i - 1) {
        sum += v[idx];
        t.push_back(v[idx]);
        idx--;
      }
      ans.push_back(std::move(t));
    }
    bool first = true;
    for (int i = ans.size() - 1; i >= 0; i--) {
      if (first) first = false;
      else cout << "/ ";
      for (int j = ans[i].size() - 1; j >= 0; j--) cout << ans[i][j] << ' ';
      cout << '\n';
    }
  }
}
