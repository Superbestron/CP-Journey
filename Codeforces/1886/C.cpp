#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  long long t, pos;
  string s;
  cin >> t;
  while (t--) {
    cin >> s >> pos;
    int curr_size = s.size(), iteration = 0;
    while (pos > curr_size) {
      pos -= curr_size;
      curr_size--;
      iteration++;
    }
    string v;
    for (char c : s) {
      while (iteration && !v.empty() && v.back() > c) {
        v.pop_back();
        iteration--;
      }
      v += c;
    }
    cout << v[pos - 1];
  }
}