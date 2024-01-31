#include<bits/stdc++.h>
using namespace std;
#define MAX 205

typedef vector<int> vi;

string s;
vi Grundy(MAX, -1), ANS, INTERVAL;

int SG(int len) {
  if (len <= 0) return 0;
  int &ans = Grundy[len];
  if (ans != -1) return ans;
  ans = 0;

  vector<bool> ok(MAX);
  for (int i = 1; i <= len; i++) {
    int L = SG(i - 1 - 2);
    int R = SG(len - i - 2);
    ok[L ^ R] = true;
  }

  // finding MEX
  for (int i = 0; i < MAX; i++)
    if (!ok[i]) return ans = i;
}

bool solve(int pos) {
  s[pos] = 'X';
  for (int i = 0; i < s.size() - 2; i++)
    // we win
    if (s[i] == 'X' && s[i + 1] == 'X' && s[i + 2] == 'X') {
      s[pos] = '.';
      return true;
    }
  for (int i = 0; i < s.size() - 1; i++)
    // confirm lose
    if (s[i] == 'X' && s[i + 1] == 'X') {
      s[pos] = '.';
      return false;
    }
  for (int i = 0; i < s.size() - 2; i++)
    // same reasoning
    if (s[i] == 'X' && s[i + 2] == 'X') {
      s[pos] = '.';
      return false;
    }

  INTERVAL.clear();
  int now = 0;
  for (char c : s) {
    if (c == '.') now++;
    else {
      INTERVAL.push_back(now);
      now = 0;
    }
  }
  INTERVAL.push_back(now);
  INTERVAL[0] += 2;
  INTERVAL.back() += 2;

  int XOR = 0;
  // only consider >= 4 as <= 3 is always a losing position
  for (int i : INTERVAL) if (i >= 4) XOR ^= Grundy[i - 4];
  s[pos] = '.';
  // XOR == 0 when it's losing position for enemy (aka winning position for us)
  return XOR == 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t; cin >> t;
  Grundy[0] = 0;
  for (int i = 1; i < MAX; i++) SG(i);
  for (int cs = 1; cs <= t; cs++) {
    cin >> s;
    ANS.clear();

    for (int i = 0; i < s.size(); i++) {
      if (s[i] == 'X') continue;
      if (solve(i)) ANS.push_back(i + 1);
    }

    if (ANS.empty()) cout << "LOSING\n";
    else {
      cout << "WINNING\n";
      for (int i = 0; i < ANS.size() - 1; i++) cout << ANS[i] << ' ';
      cout << ANS.back();
    }
    cout << '\n';
  }
}
