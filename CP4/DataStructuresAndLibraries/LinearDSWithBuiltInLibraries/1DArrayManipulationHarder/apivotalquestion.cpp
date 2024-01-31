#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int main() {
  ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  vi a(n), pref(n), suff(n), output;
  for (int &i : a) cin >> i;
  if (n == 1) {
    cout << 1 << ' ' << a[0] << ' ';
    return 0;
  }
  pref[0] = a[0];
  suff[n - 1] = a[n - 1];
  for (int i = 1; i < n; i++) pref[i] = max(a[i], pref[i - 1]);
  for (int i = n - 2; i >= 0; i--) suff[i] = min(a[i], suff[i + 1]);
  if (a[0] < suff[1]) output.push_back(a[0]);
  for (int i = 1; i < n - 1; i++) {
    if (a[i] > pref[i - 1] && a[i] < suff[i + 1]) output.push_back(a[i]);
  }
  if (a[n - 1] > pref[n - 2]) output.push_back(a[n - 1]);
  cout << output.size() << ' ';
  for (int i = 0; i < min((int) output.size(), 100); i++) cout << output[i] << ' ';
}
