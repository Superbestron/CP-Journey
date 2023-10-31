#include <bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;

int n, max_width = 0, num_ctr = 0;
unordered_map<char, int> mp;
map<int, char> mp_to_char;
vector<unordered_set<char>> col_of_chars;
vector<int> numbers;
vector<string> cpy, v;
int ans = 0;

void backtrack(int idx, int mask) {
  if (__builtin_popcount(mask) == 10 - num_ctr) {
    for (int i = 0; i < n; i++) {
      if (numbers[mp[cpy[i][0]]] == 0) return;
    }
    ans++;
    return;
  }
  int m = mask;
  while (m) {
    int pow = LSOne(m);
    int num = __builtin_ctz(pow);

    numbers[idx] = num;
    vector<int> carrys(max_width);
    // prune early
    bool can_prune = false;
//    char c = mp_to_char[idx];
    for (int j = max_width - 1; j >= 0; j--) {
      bool undefined = false;
      // for each col
//      if (!col_of_chars[j].count(c)) continue; // column doesn't involve this char
      int sum = 0;
      for (char k : col_of_chars[j]) {
        int num_idx = mp[k];
        if (numbers[num_idx] == -1) { // undefined
          undefined = true;
          break;
        }
      }
      if (undefined) {
        goto done;
      }
      // check condition
      for (int k = 0; k < n - 1; k++) {
        if (v[k][j] != '0') sum += numbers[mp[v[k][j]]];
      }
      sum += carrys[j];
      int test = numbers[mp[v[n - 1][j]]];
      if (sum % 10 != test) {
        can_prune = true;
        break;
      }
      if (sum >= 10) {
        if (j != 0) carrys[j - 1] = sum / 10;
        else {
          can_prune = true;
          break;
        }
      }
    }
    done:
    if (!can_prune) {
      backtrack(idx + 1, mask ^ pow);
    }
    numbers[idx] = -1;
    m -= pow;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  v.assign(n, "");
  for (auto& s : v) {
    cin >> s;
    max_width = max(max_width, (int) s.size());
  }
  cpy = v;
  for (auto& s : v) {
    if (s.size() != max_width) {
      s = string(max_width - s.size(), '0') + s;
    }
  }

  for (int j = max_width - 1; j >= 0; j--) {
    for (int i = 0; i < n; i++) {
      char c = v[i][j];
      if (c == '0') continue;
      if (!mp.count(c)) {
        mp_to_char[num_ctr] = c;
        mp[c] = num_ctr++;
      }
    }
  }

  numbers.assign(num_ctr, -1);
  col_of_chars.assign(max_width, {});

  for (int i = 0; i < max_width; i++) {
    for (int j = 0; j < n; j++) {
      if(v[j][i] != '0') col_of_chars[i].insert(v[j][i]);
    }
  }
  backtrack(0, (1 << 10) - 1);
  cout << ans << '\n';
}
