#include<bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  int lo = 1, hi = 1000;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    cout << mid << endl;
    cin >> s;
    if (s == "correct") return 0;
    else if (s == "lower") {
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  cout << lo << endl;
}
