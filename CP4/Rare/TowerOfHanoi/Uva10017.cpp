#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vi A, B, C;
int n, m, tc = 1, times;

void print() {
  cout << "\nA=>";
  if (!A.empty()) {
    cout << "   ";
    for (int i = 0; i < A.size() - 1; i++) cout << A[i] << ' ';
    cout << A.back();
  }
  cout << "\nB=>";
  if (!B.empty()) {
    cout << "   ";
    for (int i = 0; i < B.size() - 1; i++) cout << B[i] << ' ';
    cout << B.back();
  }
  cout << "\nC=>";
  if (!C.empty()) {
    cout << "   ";
    for (int i = 0; i < C.size() - 1; i++) cout << C[i] << ' ';
    cout << C.back();
  }
  cout << '\n';
}

void solve(int count, vi &source, vi &destination, vi &intermediate) {
  if (times > m) return;
  if (count == 1) {
    destination.push_back(source.back());
    source.pop_back();
    if (times++ <= m) print();
  } else {
    solve(count - 1, source, intermediate, destination);
    solve(1, source, destination, intermediate);
    solve(count - 1, intermediate, destination, source);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    cout << "Problem #" << tc++ << '\n';
    times = 0;
    A.clear(); B.clear(), C.clear();
    for (int i = n; i; i--) A.push_back(i);
    if (times++ <= m) print();
    solve(n, A, C, B);
    cout << '\n';
  }
}
