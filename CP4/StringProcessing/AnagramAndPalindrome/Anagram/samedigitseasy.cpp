#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<ii> vii;

int a, b;

inline void solve() {
  cin >> a >> b;
  vii ans;
  for (int i = a; i <= b; i++) {
    string str_A = to_string(i);
    vi A(10);
    for (char c : str_A) A[c - '0']++;
    for (int j = i; j <= b; j++) {
      int prod = i * j;
      vi B = A;
      string str_B = to_string(j);
      for (char c : str_B) B[c - '0']++;
      string str_C = to_string(prod);
      vi C(10);
      for (char c : str_C) C[c - '0']++;
      if (B == C) ans.emplace_back(i, j);
    }
  }
  cout << ans.size() << " digit-preserving pair(s)\n";
  for (auto &[x, y] : ans) {
    cout << "x = " << x << ", y = " << y << ", xy = " << x * y << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
