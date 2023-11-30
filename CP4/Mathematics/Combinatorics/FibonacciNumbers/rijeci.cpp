#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int K; cin >> K;
  unordered_map<char, int> m;
  m['A'] = 1;
  for (int i = 1; i <= K; i++) {
    int cntA = m['A'];
    int cntB = m['B'];
    m['A'] += cntB;
    m['B'] += cntA;
    m['A'] -= cntA;
  }
  cout << m['A'] << ' ' << m['B'];
}
