#include<bits/stdc++.h>
using namespace std;
#define MAX_N 101
typedef vector<int> vi;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, p1 = 0, p2 = 0, p1_lead = 0, p2_lead = 0, p1_streak = 0, p2_streak = 0, prev = 0, streak = 0;
  cin >> N;
  string s;
  for (int i = 0; i < N; i++) {
    cin >> s;
    if (s == "Yraglac") {
      p1++;
      if (prev == 1) streak++;
      else {
        p2_streak = max(p2_streak, streak);
        streak = 1;
      }
    } else {
      p2++;
      if (prev == 2) streak++;
      else {
        p1_streak = max(p1_streak, streak);
        streak = 1;
      }
    }
    prev = s == "Yraglac" ? 1 : 2;
    p1_lead = max(p1_lead, p1 - p2);
    p2_lead = max(p2_lead, p2 - p1);
  }
  if (s == "Yraglac") p1_streak = max(p1_streak, streak);
  else p2_streak = max(p2_streak, streak);
  if (p1_lead > p2_lead && p1_streak > p2_streak || p1_lead == p2_lead && p1_streak == p2_streak
    || p1_lead < p2_lead && p1_streak < p2_streak) cout << "Agree\n";
  else cout << "Disagree\n";
}
