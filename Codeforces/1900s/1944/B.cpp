#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, k;

void solve() {
  cin >> n >> k;
  vi a(2 * n);
  for (int &i : a) cin >> i;
  unordered_map<int, int> mp1, mp2;
  for (int i = 0; i < n; i++) {
    mp1[a[i]]++;
  }
  for (int i = n; i < 2 * n; i++) {
    mp2[a[i]]++;
  }
  int need1 = 2 * k, need2 = 2 * k;
  for (auto &[num, cnt] : mp1) {
    if (need1 >= 2 && cnt == 2) {
      cout << num << ' ' << num << ' ';
      need1 -= 2;
    }
  }
  set<int> s;
  for (auto &[num, cnt] : mp1) {
    if (need1 >= 1 && cnt == 1) {
      cout << num << ' ';
      s.insert(num);
      need1--;
    }
  }
  cout << '\n';
  for (auto &[num, cnt] : mp2) {
    if (need2 >= 2 && cnt == 2) {
      cout << num << ' ' << num << ' ';
      need2 -= 2;
    }
  }
  for (int i : s) cout << i << ' ';
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