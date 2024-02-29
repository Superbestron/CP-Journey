#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;

int t, a, b, l;

void solve() {
  cin >> a >> b >> l;
  unordered_set<int> s;
  int a_sum = 1;
  while (a_sum <= l) {
    int b_sum = 1;
    while (a_sum * b_sum <= l) {
      if (l % (a_sum * b_sum) == 0) {
        s.insert(l / (a_sum * b_sum));
      }
      b_sum *= b;
    }
    a_sum *= a;
  }
  cout << s.size() << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}
