#include <bits/stdc++.h>
using namespace std;

string s, letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
set<pair<int, string>> st;

void backtrack(int moves) {
  if (st.count({moves, s})) return;
  st.emplace(moves, s);
  if (moves == 0) return;
  for (int i = 0; i < s.size() - 1; i++) {
    swap(s[i], s[i + 1]);
    backtrack(moves - 1);
    swap(s[i + 1], s[i]);
  }
}

bool check(int moves) {
  for (int i = moves; i <= 3; i++) {
    if (st.count({i, s})) return true;
  }
  if (moves == 3) return false;
  bool ans = false;
  for (int i = 0; i < s.size() && !ans; i++) {
    if (!isdigit(s[i])) continue;
    for (int j = 0; j < 52 && !ans; j++) {
      char temp = s[i];
      s[i] = letters[j];
      ans |= check(moves + 1);
      s[i] = temp;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> s;
    backtrack(3);
  }
  while (cin >> s) {
    int digits = 0;
    for (char i : s) {
      if (isdigit(i)) {
        digits++;
      }
    }
    if (digits > 3 || !check(0)) cout << s << '\n';
  }
}
