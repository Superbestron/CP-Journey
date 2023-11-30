#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  unordered_map<ll, ll> memo;
  for (ll a = 0; a <= 2000001; a++) {
    memo[a * a] = a;
  }

  int num_balls;
  cin >> num_balls;
  int count_req = 0;
  while (num_balls) {
    cout << 0 << " " << 0 << '\n';
    cout.flush();
    ll d;
    count_req++;
    cin >> d;
    if (d == 0) {
      num_balls--;
      continue;
    }
    for (ll a = 0; a * a <= d * 2; a++) {
      ll b = d - a * a;
      if (memo.find(b) == memo.end()) {
        continue;
      }
      const ll root = memo[b];
      if (root > 1000000 || a > 1000000)
        continue;
      pair<ll, ll> possibleOne = {a, root};
      pair<ll, ll> possibleTwo = {root, a};
      cout << possibleOne.first << " " << possibleOne.second << '\n';
      cout.flush();
      count_req++;
      ll triedDist;
      cin >> triedDist;
      if (triedDist == 0) {
        break;
      } else {
        if (a == root) {
          continue;
        }
        cout << possibleTwo.first << " " << possibleTwo.second << '\n';
        cout.flush();
        count_req++;
        ll secondTriedDist;
        cin >> secondTriedDist;
        if (secondTriedDist == 0) {
          break;
        }
      }
    }
    num_balls--;
  }
}
