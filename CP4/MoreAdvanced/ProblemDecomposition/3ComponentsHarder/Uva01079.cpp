#include <bits/stdc++.h>
using namespace std;

int n, order[8];
double a[8], b[8], L;

bool greedyLanding() { // with certain landing order, and certain L,
  // try landing those planes and see what is the gap to b[order[n-1]]
  double lastLanding = a[order[0]];              // greedy for 1st aircraft
  for (int i = 1; i < n; ++i) {                  // for the other aircrafts
    double targetLandingTime = lastLanding + L;
    if (targetLandingTime <= b[order[i]])
      // can land: greedily choose max of a[order[i]] or targetLandingTime
      lastLanding = max(a[order[i]], targetLandingTime);
    else return false;
  }
  return true;
}

int main() {
  int caseNo = 1;
  while (cin >> n) {                   // 2 <= n <= 8
    if (n == 0) break;
    for (int i = 0; i < n; ++i) {                // plane i land at [ai,bi]
      cin >> a[i] >> b[i];
      a[i] *= 60;
      b[i] *= 60;                    // convert to seconds
      order[i] = i;
    }
    double maxL = -1.0;                          // the answer
    do {                                         // permute landing order
      double lo = 0, hi = 86400;                 // min 0s, max 86400s
      L = -1;
      for (int i = 0; i < 30; ++i) {             // BSTA (L)
        L = (lo + hi) / 2.0;
        greedyLanding() ? lo = L : hi = L;      // increase/decrease L
      }
      maxL = max(maxL, L);                       // the max overall
    } while (next_permutation(order, order + n));     // try all permutations

    int secs = lround(maxL);                     // round to nearest second
    cout << "Case " << caseNo++ << ": " << secs / 60 << ':' << setfill('0') << setw(2) << secs % 60 << '\n';
  }
}
