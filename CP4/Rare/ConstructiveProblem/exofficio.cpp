#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) cout << " _";
  cout << "\n";
  if (n & 1) {
    for (int i = 0; i < n / 2; i++) {
      for (int j = 0; j < m; j++) cout << "| ";
      cout << "|\n";
    }
    if (n != 1) {
      cout << '|';
      for (int i = 0; i < m * 2 - 1; i++) cout << ' ';
      cout << "|\n";
    }
    for (int i = 0; i < n / 2 - 1; i++) {
      for (int j = 0; j < m; j++) cout << "| ";
      cout << "|\n";
    }
    if (n != 1) for (int j = 0; j < m; j++) cout << "|_";
    else {
      cout << "|_";
      for (int j = 1; j < m; j++) cout << " _";
    }
    cout << "|";
  } else {
    for (int j = 0; j < n - 1; j++) {
      cout << "|";
      for (int i = 1; i < m / 2 + (m&1 ? 1 : 0); i++) cout << "_ ";
      cout << " ";
      for (int i = 1; i < m / 2 + 1; i++) cout << " _";
      cout << "|\n";
    }
    cout << "|_";
    for (int i = 1; i < m; i++) cout << " _";
    cout << "|";
  }
}
