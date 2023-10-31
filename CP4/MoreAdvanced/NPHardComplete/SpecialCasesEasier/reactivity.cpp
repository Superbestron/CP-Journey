#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pi;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K, a, b;
  cin >> N >> K;
  vector<vector<int>> AL(N);
  vector<int> in_deg(N);
  for (int i = 0; i < K; i++) {
    cin >> a >> b;
    AL[a].push_back(b);
    in_deg[b]++;
  }
  queue<int> pq;
  for (int i = 0; i < N; i++) {
    if (in_deg[i] == 0) pq.push(i);
  }
  vector<int> ans;
  while (!pq.empty()) {
    if (pq.size() > 1) {
      cout << "back to the lab";
      return 0;
    }
    auto idx = pq.front(); pq.pop();
    ans.push_back(idx);
    for (int v : AL[idx]) {
      in_deg[v]--;
      if (in_deg[v] == 0) pq.push(v);
    }
  }
  for (int i : ans) cout << i << ' ';
}