#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;

  // idea: prefix either "", "a" or "aa" then append ba or baa behind until n and m is satisfied
  // let a and b be the number of ba and baa after removing prefix
  // solve simultaneous: 2a + 3b = n; 24a + 28b = m;

  // if odd, definitely starts with aa, then append ba or baa behind
  int a, b; // a represents ba, b represents baa
  string ans;
  if (m % 2 == 1) {
    n -= 2;
    m -= 29;
    if (12 * n - m >= 0 && (12 * n - m) % 8 == 0) {
      b = (12 * n - m) / 8;
      a = (n - 3 * b) / 2;
      if (a >= 0) {
        cout << "aa";
        for (int i = 0; i < a; i++)
          cout << "ba";
        for (int j = 0; j < b; j++)
          cout << "baa";
        cout << '\n';
        return 0;
      }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  // start with "" and append ba or baa behind
  if (12 * n - m >= 0 && (12 * n - m) % 8 == 0) {
    b = (12 * n - m) / 8;
    a = (n - 3 * b) / 2;
    // cannot start with bab... so prefix need to be baa
    if (a >= 0 && b > 0) {
      for (int j = 0; j < b; j++)
        cout << "baa";
      for (int i = 0; i < a; i++)
        cout << "ba";
      cout << '\n';
      return 0;
    }
  }
  // start with a and append ba or baa behind
  n--;
  m -= 4;
  if (12 * n - m >= 0 && (12 * n - m) % 8 == 0) {
    b = (12 * n - m) / 8;
    a = (n - 3 * b) / 2;
    if (a >= 0) {
      cout << "a";
      for (int j = 0; j < b; j++)
        cout << "baa";
      for (int i = 0; i < a; i++)
        cout << "ba";
      cout << '\n';
      return 0;
    }
  }
  cout << "IMPOSSIBLE\n";
}
