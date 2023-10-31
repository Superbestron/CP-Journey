#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s1, s2, s1ans, s2ans;
  cin >> s1 >> s2;
  int len = max(s1.size(), s2.size());
  int s1_sz = s1.size(), s2_sz = s2.size();
  for (int i = 0; i < len - s1_sz; i++) s1 = '0' + s1;
  for (int i = 0; i < len - s2_sz; i++) s2 = '0' + s2;
  for (int i = 0; i < len; i++) {
    if (s1[i] == s2[i]) {
      s1ans += s1[i];
      s2ans += s2[i];
    } else if (s1[i] < s2[i]) s2ans += s2[i];
    else s1ans += s1[i];
  }
  if (s1ans.empty()) cout << "YODA\n";
  else cout << stoi(s1ans) << '\n';
  if (s2ans.empty()) cout << "YODA\n";
  else cout << stoi(s2ans) <<  '\n';
}