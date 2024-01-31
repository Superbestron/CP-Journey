#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool all_same(vector<int>& v) {
  int curr = v[0];
  for (int i = 1; i < v.size(); i++) {
    if (v[i] != curr) {
      return false;
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, a, b, c;
  cin >> t;
  while (t--) {
    cin >> a >> b >> c;
    if (a == b && b == c) {
      cout << "YES\n";
      continue;
    }
    vector<int> v{a, b, c};
    sort(v.begin(), v.end());
    int cnt = 3;
    while (cnt && !all_same(v)) {
      int big = v.back(); v.pop_back();
      v.push_back(big - v.front());
      v.push_back(v.front());
      cnt--;
      sort(v.begin(), v.end());
    }
    if (all_same(v)) cout << "YES\n";
    else cout <<"NO\n";
  }
}