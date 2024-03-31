#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int main() {
  int n;
  cin >> n;
  vi arr(n);
  for (int &i : arr) cin >> i;
  vi s, t;
  for (int i = 1; i < n - 1; ++i) s.push_back(i);
  for (int i = 2; i < n; ++i) s.push_back(i);
  sort(s.begin(), s.end());

  int lim = n - 2;
  priority_queue<int, vi, greater<>> pq;

  while ((int) t.size() != n - 2) {
    if (!s.empty() && s.back() >= lim) {
      pq.push(arr[s.back()]);
      s.pop_back();
    } else {
      lim--;
      t.push_back(pq.top());
      pq.pop();
    }
  }

  ll sum = accumulate(t.begin(), t.end(), 0LL);
  cout << sum + arr[n - 1] << '\n';
}
