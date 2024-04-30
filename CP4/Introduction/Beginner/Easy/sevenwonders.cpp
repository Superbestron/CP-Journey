#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  int t_count = 0, c_count = 0, g_count = 0;
  for (char c : s) {
    if (c == 'T') t_count++;
    else if (c == 'C') c_count++;
    else g_count++;
  }
  cout << t_count * t_count + c_count * c_count + g_count * g_count + 7 * min({t_count, c_count, g_count}) << '\n';
}
