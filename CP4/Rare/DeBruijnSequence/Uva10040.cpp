#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vector<vi> AL, paths(22);
int T, N, K, v;

vi hierholzer(int s) {
  vi ans, idx(v, 0), st;
  st.push_back(s);
  while (!st.empty()) {
    int u = st.back();
    if (idx[u] < (int)AL[u].size()) { // still has neighbor
      st.push_back(AL[u][idx[u]]);
      ++idx[u];
    }
    else {
      ans.push_back(u);
      st.pop_back();
    }
  }
  ans.pop_back();
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for (int n = 2; n <= 21; n++) {
    v = 1 << (n - 1);
    AL.assign(v, {});
    // generate de bruijn graph
    for (int i = 0; i < v; i++) {
      int k = i % (v >> 1);  // chop off first digit
      k <<= 1;  // append digit to back
      for (int j = 0; j < 2; j++) {
        AL[i].emplace_back(k + j);
      }
    }
    paths[n] = hierholzer(v - 1);
  }

  while (T--) {
    cin >> N >> K;
    if (N == 1) {  // important edge case
      cout << K << '\n';
      continue;
    }

    int x = 0;
    for (int i = 0; i < N; i++) {
      x <<= 1;
      x += paths[N][(K + i) % (paths[N].size())] & 1;  // get last digit
    }
    cout << x << '\n';
  }
}
