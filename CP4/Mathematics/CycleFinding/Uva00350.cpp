#include <bits/stdc++.h>
using namespace std;

int Z, I, M, L, tc = 1;

inline int f(int L) {
  return (Z * L + I) % M;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> Z >> I >> M >> L) {
    if (Z == 0 && I == 0 && M == 0 && L == 0) break;
    int t = f(L), h = f(f(L));
    while (t != h) {
      t = f(t);
      h = f(f(h));
    }
    int mu = 0;
    h = L;
    while (t != h) {
      t = f(t);
      h = f(h);
      mu++;
    }
    int lambda = 1;
    h = f(t);
    while (t != h) {
      h = f(h);
      lambda++;
    }
    printf("Case %d: %d\n", tc++, lambda);
  }
}
