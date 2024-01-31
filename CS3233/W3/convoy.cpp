#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef tuple<ll, ll> ii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  vi a(n);
  for (int &i : a) cin >> i;
  vector<bool> car(n);
  sort(a.begin(), a.end());
  priority_queue<ii, vector<ii>, greater<>> pq;
  for (int i = 0; i < min(n, k); i++) pq.emplace(a[i], i);
  ll ppl = n, ans = 0;
  while (ppl > 0) {
    auto [time, idx] = pq.top(); pq.pop();
    ans = time;
    if (car[idx]) ppl -= 4;
    else ppl -= 5;
    car[idx] = true;
    pq.emplace(time + 2 * a[idx], idx);
  }
  cout << ans << '\n';
}
