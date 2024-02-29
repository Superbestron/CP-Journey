#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<ll, ll> ii;
const double EPS = 1e-9;

vector<vi> AL(200);
vi dist;

int dfs(int len, int u) {
  dist[u] = 1;
  int max_len = 0;
  for (int v : AL[u]) {
    if (dist[v] == -1) max_len = max(dfs(len + 1, v), max_len);
    else max_len = max(len + 1, max_len);
  }
  return max_len;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n; cin >> n;
  string name, has, wants;
  unordered_map<string, int> mp;
  for (int i = 0; i < n; i++) {
    cin >> name >> has >> wants;
    if (!mp.count(has)) {
      mp[has] = mp.size();
    }
    if (!mp.count(wants)) {
      mp[wants] = mp.size();
    }
    int idx1 = mp[has], idx2 = mp[wants];
    AL[idx1].push_back(idx2);
    dist.assign(mp.size(), -1);
  }
  int max_len = 0;
  for (int i = 0; i < mp.size(); i++) {
    if (dist[i] == -1) {
      max_len = max(max_len, dfs(0, i));
    }
  }
  if (max_len == 0) cout << "No trades possible\n";
  else cout << max_len << '\n';
}
