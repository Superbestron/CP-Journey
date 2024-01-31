#include<bits/stdc++.h>
using namespace std;

unordered_map<int, int> mp;

bool backtrack(int num, int mentsu) {
  if (mentsu == 4) return true;
  bool ans = false;
  if (mp[num] >= 3) {
    mp[num] -= 3;
    ans |= backtrack(num, mentsu + 1);
    mp[num] += 3;
  }
  if (num <= 7 && mp[num] && mp[num + 1] && mp[num + 2]) {
    mp[num]--; mp[num + 1]--; mp[num + 2]--;
    ans |= backtrack(num, mentsu + 1);
    mp[num]++; mp[num + 1]++; mp[num + 2]++;
  }
  if (mp[num] == 0) ans |= backtrack(num + 1, mentsu);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N; cin >> N;
  char ch;
  for (int i = 0; i < N; i++) {
    mp.clear();
    for (int j = 0; j < 13; j++) {
      cin >> ch;
      mp[ch - '0']++;
      cin >> ch;
    }
    bool ans = false;
    for (int missing = 1; missing <= 9 && !ans; missing++) {
      if (mp[missing] == 4) continue;
      mp[missing]++;
      for (int jantou = 1; jantou <= 9 && !ans; jantou++) {
        if (mp[jantou] >= 2) {
          mp[jantou] -= 2;
          ans = backtrack(1, 0);
          mp[jantou] += 2;
        }
      }
      mp[missing]--;
    }
    if (ans) cout << "Riichi!\n";
    else cout << ":(\n";
  }
}
