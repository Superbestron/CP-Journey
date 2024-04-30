#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, x;
  cin >> n >> x;
  ll max_pos = ((n - 3) + 2) * (n - 2) / 2;
  if (x > max_pos) {
    cout << "-1\n";
    return 0;
  }
  ll smallest = 1;
  cout << n << ' ';
  while (x - (n - 1 - smallest) >= 0 && (n - 1 - smallest) > 0) {
    cout << smallest << ' ';
    x -= (n - 1 - smallest);
    smallest++;
  }
  ll used = -1;
  if (x) {
    cout << n - 1 - x << ' ';
    used = n - 1 - x;
  }
  cout << n - 1 << ' ';
  for (ll i = n - 2; i >= smallest; i--) {
    if (i == used) continue;
    cout << i << ' ';
  }
  cout << '\n';
}
