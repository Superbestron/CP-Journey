#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int x;
  vector<int> a;
  while (cin >> x) {
    a.push_back(x);
  }
  int n = a.size();
  sort(a.begin(), a.end());
  int i = n;
  ll sum = 0;
  while (sum + a[i - 1] >= 0 && i - 1 >= 0) {
    sum += a.at(i - 1);
    i--;
  }
  sum = 0;
  for (ll ctr = i, multi = 1; ctr < n; ctr++, multi++) {
    sum += multi * a.at(ctr);
  }
  cout << sum << '\n';
}
