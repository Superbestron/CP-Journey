#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

// Interesting problem... It stumped me initially so I look on the internet for inspiration :)
// It's simple to solve on paper in a probability exam but on code, we need to do simulation
// One way is to use a bellman-ford-like simulation, where we "relax" edges by moving probabilities
// to neighbouring nodes, for a set number of iterations.

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M;
  ld ans = 0;
  cin >> N >> M;
  vector<vector<int>> AL(N);
  vector<ld> prob(N), old_prob;
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    AL[a].push_back(b);
    AL[b].push_back(a);
  }
  int upper_bound = 10000;
  prob[0] = 1;
  for (int l = 1; l < upper_bound; l++) {
    old_prob = prob;
    prob.assign(N, 0);
    for (int i = 0; i < N - 1; i++) {
      for (int v : AL[i]) {
        prob[v] += old_prob[i] / AL[i].size();
      }
    }
    ans += prob[N - 1] * l;
  }
  cout << setprecision(5) << fixed << ans;
}
