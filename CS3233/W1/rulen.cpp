#include<bits/stdc++.h>
using namespace std;
#define MAX_N 101
typedef vector<int> vi;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, L, R;
  string s;
  cin >> N >> L >> R >> s;
  vector<string> A {"000", "001", "010", "011", "100", "101", "110", "111"};
  unordered_map<string, bool> m;
  for (int i = 0; i < 8; i++) {
    bool is_set = N & 1;
    m[A[i]] = is_set;
    N >>= 1;
  }
  string extra(MAX_N + 1, '0');
  s = extra + s;
  s += extra;
  for (int i = 0; i < R; i++) {
    string new_s;
    for (int j = 0; j < s.size() - 2; j++) {
      string to_compare = s.substr(j, 3);
      new_s += m[to_compare] ? '1' : '0';
    }
    cout << new_s.substr(MAX_N - i, L) << '\n';
    s = new_s;
  }
}
