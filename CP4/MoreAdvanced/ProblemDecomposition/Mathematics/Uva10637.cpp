#include <bits/stdc++.h>
using namespace std;

int N, S, t;

vector<int> output;

void recurse(int val, int num) {
  if (num == 0) {
    if (val == 0) {
      cout << output[0];
      for (int i = 1; i < output.size(); i++) cout << ' ' << output[i];
      cout << '\n';
    }
    return;
  }

  int i;
  if (output.empty()) i = 1;
  else i = output.back();
  for (; i <= val; i++) {
    bool can = true;
    for (int j : output) {
      if (gcd(i, j) != 1) {
        can = false;
        break;
      }
    }
    if (can) {
      output.push_back(i);
      recurse(val - i, num - 1);
      output.pop_back();
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> S >> t;
    cout << "Case " << i << ':' << '\n';
    recurse(S, t);
  }
}
