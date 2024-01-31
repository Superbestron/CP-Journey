#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<ll, ll> ii;
typedef vector<ii> vii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, Y, x;
  unordered_set<int> s;
  cin >> N >> Y;
  for (int i = 0; i < Y; i++) {
    cin >> x;
    s.insert(x);
  }
  for (int i = 0; i < N; i++) {
    if (!s.count(i)) cout << i << '\n';
  }
  cout << "Mario got " << s.size() << " of the dangerous obstacles.\n";
}
