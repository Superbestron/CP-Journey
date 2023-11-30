#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 2;                             // 2x2 for Fib matrix
struct Matrix { ll mat[MAX_N][MAX_N]; };         // we return a 2D array

Matrix matMul(Matrix a, Matrix b) {              // normally O(n^3)
  Matrix ans;                                    // but O(1) as n = 2
  for (auto &i : ans.mat)
    for (ll &j : i)
      j = 0;
  for (int i = 0; i < MAX_N; ++i)
    for (int k = 0; k < MAX_N; ++k) {
      if (a.mat[i][k] == 0) continue;            // optimization
      for (int j = 0; j < MAX_N; ++j) {
        ans.mat[i][j] += a.mat[i][k] * b.mat[k][j];
        ans.mat[i][j] = ans.mat[i][j]; // modular arithmetic
      }
    }
  return ans;
}

Matrix matPow(Matrix base, int p) {              // normally O(n^3 log p)
  Matrix ans;                                    // but O(log p) as n = 2
  for (int i = 0; i < MAX_N; ++i)
    for (int j = 0; j < MAX_N; ++j)
      ans.mat[i][j] = (i == j);                  // prepare identity matrix
  while (p) {                                    // iterative D&C version
    if (p & 1)                                     // check if p is odd
      ans = matMul(ans, base);                   // update ans
    base = matMul(base, base);                   // square the base
    p >>= 1;                                     // divide p by 2
  }
  return ans;
}

vector<string> split(string& s, char delimiter) {
  size_t pos;
  string token;
  vector<string> arr;
  if (s.empty()) return arr;
  while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    arr.emplace_back(token);
    s.erase(0, pos + 1);
  }
  arr.emplace_back(s);
  return arr;
}

int main() {
  int p, q, n;
  string s;
  while (getline(cin, s)) {
    vector<string> v(split(s, ' '));
    if (v.size() == 2) break;
    p = stoi(v[0]);
    q = stoi(v[1]);
    n = stoi(v[2]);
    Matrix ans;                                  // Fibonaccci matrix
    ans.mat[0][0] = p;
    ans.mat[0][1] = -q;
    ans.mat[1][0] = 1;
    ans.mat[1][1] = 0;
    ans = matPow(ans, n);                        // O(log n)
    cout << ans.mat[1][0] * p + ans.mat[1][1] * 2 << '\n';
  }
}
