#include <bits/stdc++.h>
using namespace std;

int least_rotation(vector<int> &s) {
  int n = s.size();
  vector<int> f(2 * n, -1);
  int k = 0;
  for (int j = 1; j < 2 * n; j++) {
    int i = f[j - k - 1];
    while (i != -1 && s[j % n] != s[(k + i + 1) % n]) {
      if (s[j % n] < s[(k + i + 1) % n]) {
        k = j - i - 1;
      }
      i = f[i];
    }
    if (i == -1 && s[j % n] != s[(k + i + 1) % n]) {
      if (s[j % n] < s[(k + i + 1) % n]) k = j;
      f[j - k] = -1;
    } else f[j - k] = i + 1;
  }
  return k;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n; cin >> n;
  vector<int> a(n), b(n), a_diff, b_diff;
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  for (int i = 0; i < n - 1; i++) {
    a_diff.push_back(a[i + 1] - a[i]);
    b_diff.push_back(b[i + 1] - b[i]);
  }
  a_diff.push_back(360000 - (a[n - 1] - a[0]));
  b_diff.push_back(360000 - (b[n - 1] - b[0]));
  rotate(a_diff.begin(), a_diff.begin() + least_rotation(a_diff), a_diff.end());
  rotate(b_diff.begin(), b_diff.begin() + least_rotation(b_diff), b_diff.end());

  if (a_diff == b_diff) cout << "possible\n";
  else cout << "impossible\n";
}
