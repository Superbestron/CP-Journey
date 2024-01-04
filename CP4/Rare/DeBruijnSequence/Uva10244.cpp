#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;

vector<vi> AL;
string str;
int M, N, v;

vector<int> hierholzer(int s) {
  vi ans, idx(v, 0), st;
  st.push_back(s);
  while (!st.empty()) {
    int u = st.back();
    if (idx[u] < AL[u].size()) {  // still has neighbor
      st.push_back(AL[u][idx[u]]);
      ++idx[u];
    } else {
      ans.push_back(u);
      st.pop_back();
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> str >> M) {
    N = str.size();
    v = pow(N, M - 1);

    ll len = (ll) pow(N, M) + M - 1;
    cout << len << '\n';
    if (len > 10000) {
      cout << "TOO LONG TO PRINT.\n";
      continue;
    }

    AL.assign(v, {});

    // generate de bruijn graph
    for (int i = 0; i < v; i++) {
      int k = i % (v / N);  // chop off first digit
      k *= N;  // append digit to back
      for (int j = 0; j < N; j++) {
        AL[i].emplace_back(k + j);
      }
    }

    vi path(hierholzer(0));
    string ans;
    for (int i = 0; i < path.size() - 1; i++) {
      ans += str[path[i] % N];  // get last digit
    }
    for (int i = 0; i < M - 1; i++) ans += ans[i];

    cout << ans << '\n';
  }
}
