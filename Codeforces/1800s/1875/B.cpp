#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, m, k;
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    vector<int> J(n), G(m);
    deque<int> J_d, G_d;
    for (int& i : J) cin >> i;
    for (int& i : G) cin >> i;
    sort(J.begin(), J.end());
    sort(G.begin(), G.end());
    for (int& j : J) J_d.push_back(j);
    for (int& j : G) G_d.push_back(j);
    for (int i = 0; i < (min(k, 50) / 2); i++) {
      if (J_d.front() < G_d.back()) {
        int j_temp = J_d.front(); J_d.pop_front();
        int g_temp = G_d.back(); G_d.pop_back();
        J_d.push_back(g_temp); G_d.push_front(j_temp);
        J = vector<int>(J_d.begin(), J_d.end());
        sort(J.begin(), J.end());
        G = vector<int>(G_d.begin(), G_d.end());
        sort(G.begin(), G.end());
        J_d.clear(); G_d.clear();
        for (int& j : J) J_d.push_back(j);
        for (int& j : G) G_d.push_back(j);
      }
      if (G_d.front() < J_d.back()) {
        int g_temp = G_d.front(); G_d.pop_front();
        int j_temp = J_d.back(); J_d.pop_back();
        G_d.push_back(j_temp); J_d.push_front(g_temp);
        J = vector<int>(J_d.begin(), J_d.end());
        sort(J.begin(), J.end());
        G = vector<int>(G_d.begin(), G_d.end());
        sort(G.begin(), G.end());
        J_d.clear(); G_d.clear();
        for (int& j : J) J_d.push_back(j);
        for (int& j : G) G_d.push_back(j);
      }
    }
    long long ans = accumulate(J.begin(), J.end(), 0LL);
    if (k & 1) {
      if (J.front() < G.back()) {
        ans += G.back() - J.front();
      }
    }
    cout << ans << '\n';
  }
}