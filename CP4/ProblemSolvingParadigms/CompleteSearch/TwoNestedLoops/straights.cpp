#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<ll, ll> ii;
const double EPS = 1e-9;

vi freq(10002);

int count(int l, int r) {
  if (l > r) return 0;
  if (l == r) return freq[l];
  int min_cnt = *min_element(freq.begin() + l, freq.begin() + r + 1);
  for (int i = l; i <= r; i++) freq[i] -= min_cnt;
  int lo = l, ans = min_cnt;
  for (int i = l; i <= r + 1; i++) {
    if (freq[i] == 0) {
      ans += count(lo, i - 1);
      lo = i + 1;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n; cin >> n;
  vi a(n);
  for (int &i : a) {
    cin >> i;
    freq[i]++;
  }
  cout << count(1, 10000) << '\n';
}
