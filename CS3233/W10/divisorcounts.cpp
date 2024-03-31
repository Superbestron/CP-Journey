#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n; cin >> n;
  vi div(n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j * i <= n; j++) div[i * j]++;
    cout << div[i] << '\n';
  }
}
