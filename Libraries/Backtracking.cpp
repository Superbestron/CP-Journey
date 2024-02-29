#include<bits/stdc++.h>
#define LSOne(S) S & (-S)
using namespace std;
typedef vector<int> vi;

int main() {
  // iterate all subsets technique O(3^n)
  int mask = 137; // (10001001)_2
  for (int ss = mask; ss; ss = (ss - 1) & mask) {  // new technique
    cout << ss << "\n"; // ss is a subset of mask
  }

  // iterate all ones of the bitmask
  for (int bm = mask; bm; bm -= LSOne(bm)) {
    int idx = __builtin_ctz(bm);
  }

  vi a;
  do {
    // iterate through all permutations
  } while (next_permutation(a.begin(), a.end()));
}
