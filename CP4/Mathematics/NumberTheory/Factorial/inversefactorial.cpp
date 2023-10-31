#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string n; cin >> n;
  if (n.size() <= 6) {
    unordered_map<int, int> m;
    int sum = 1;
    for (int i = 1; i <= 10; i++) {
      sum *= i;
      m[sum] = i;
    }
    cout << m[stoi(n)];
    return 0;
  }
  unordered_map<int, int> m;
  double curr = log10(3628800);
  for (int i = 11; i <= 1000000; i++) {
    curr += log10(i);
    m[floor(curr) + 1] = i;
  }
  cout << m[n.size()];
}