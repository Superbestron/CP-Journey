#include <bits/stdc++.h>
using namespace std;

int main() {
  int N; scanf("%d", &N);
  while (N--) {
    int A, B, C; scanf("%d %d %d", &A, &B, &C);
    bool sol = false; int x, y, z;
    for (x = -22; (x <= 22) && !sol; ++x) if (x*x <= C)
        for (y = -100; (y <= 100) && !sol; ++y) if ((y != x) && (x*x + y*y <= C))
            for (z = -100; (z <= 100) && !sol; ++z)
              if ((z != x) && (z != y) &&
                  (x+y+z == A) && (x*y*z == B) && (x*x + y*y + z*z == C)) {
                printf("%d %d %d\n", x, y, z);
                sol = true;
              }
    if (!sol) printf("No solution.\n");
  }
  return 0;
}