#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  string s;
  unordered_map<string, int> m;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> s;
    cout << m[s] << '\n';
    while (!s.empty()) {
      m[s]++;
      s.pop_back();
    }
  }
}
