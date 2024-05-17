#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

const int p = 131;                        // p and M are
const int M = 1e9 + 7;                    // relatively prime

// Knuth-Morris-Pratt's algorithm specific code
// Finding all occurrences of pattern P in string T
class KMP {
 private:
  int n, m;
  vi b;                                            // b = back table
  const string T, P;
 public:
  KMP(const string &T, const string &P) : T(T), P(P) {
    n = T.size();
    m = P.size();
    int i = 0, j = -1;
    b.assign(n, 0);
    b[0] = -1;                                     // starting values
    while (i < m) {                                // pre-process P
      while ((j >= 0) && (P[i] != P[j])) j = b[j]; // different, reset j
      ++i; ++j;                                    // same, advance both
      b[i] = j;
    }
  }
  int kmpSearch() {                               // similar as above
    int freq = 0;
    int i = 0, j = 0;                              // starting values
    int prev = -1;
    while (i < n) {                                // search through T
      while ((j >= 0) && (T[i] != P[j])) j = b[j]; // if different, reset j
      ++i;
      ++j;                                    // if same, advance both
      if (j == m) {                                // a match is found
        if (prev + m <= i) {                       // comment out if allowing overlapping
          ++freq;
          prev = i;
        }
        // printf("P is found at index %d in T\n", i-j);
        j = b[j];                                  // prepare j for the next
      }
    }
    return freq;
  }
};
};

// Booth's algorithm KMP-variant, find minimum lexicographic rotation of string
int least_rotation(const string& s) {
  int n = s.size();
  vector<int> f(2 * n, -1);
  int k = 0;
  for (int j = 1; j < 2 * n; j++) {
    int i = f[j - k - 1];
    while (i != -1 && s[j % n] != s[(k + i + 1) % n]) {
      if (s[j % n] < s[(k + i + 1) % n]) {
        k = j - i - 1;
      }
      i = f[i];
    }
    if (i == -1 && s[j % n] != s[(k + i + 1) % n]) {
      if (s[j % n] < s[(k + i + 1) % n]) k = j;
      f[j - k] = -1;
    } else f[j - k] = i + 1;
  }
  return k;
}

int extEuclid(int a, int b, int &x, int &y) {    // pass x and y by ref
  int xx = y = 0;
  int yy = x = 1;
  while (b) {                                    // repeats until b == 0
    int q = a / b;
    tie(a, b) = tuple(b, a % b);
    tie(x, xx) = tuple(xx, x - q * xx);
    tie(y, yy) = tuple(yy, y - q * yy);
  }
  return a;                                      // returns gcd(a, b)
}

int modInverse(int b, int m) {                   // returns b^(-1) (mod m)
  int x, y;
  int d = extEuclid(b, m, x, y);                 // to get b*x + m*y == d
  if (d != 1) return -1;                         // to indicate failure
  // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
  return (x + m) % m;                                // this is the answer
}

// Rabin-Karp's algorithm specific code
class RabinKarp {
 private:
  vi h;                                            // to store prefix hashes
 public:
  vi Pow;                                          // to store p^i % M
  // compute Rolling Hash
  RabinKarp(const string &T) {                     // Overall: O(n)
    int n = T.size();
    h.assign(n, 0);
    Pow.assign(n, 0);
    Pow[0] = 1;                                    // compute p^i % M
    for (int i = 1; i < n; ++i)                    // O(n)
      Pow[i] = ((ll) Pow[i - 1] * p) % M;
    for (int i = 0; i < n; ++i) {                  // O(n)
      if (i != 0) h[i] = h[i - 1];                 // rolling hash
      h[i] = (h[i] + ((ll) T[i] * Pow[i]) % M) % M;
    }
  }
  int hash_fast(int L, int R) {                    // O(1) hash of any substr
    if (L == 0) return h[R];                       // h is the prefix hashes
    int ans = ((h[R] - h[L - 1]) % M + M) % M;     // compute differences
    ans = ((ll) ans * modInverse(Pow[L], M)) % M;  // remove P[L]^-1 (mod M)
    return ans;
  }
};

int main() {
  string T = "I DO NOT LIKE SEVENTY SEV BUT SEVENTY SEVENTY SEVEN";
  string P = "SEVENTY SEVEN";
  int n = T.size(), m = P.size();

  printf("T = '%s'\n", T.c_str());
  printf("P = '%s'\n", P.c_str());
  printf("\n");

  printf("String Library, #match = ");
  int pos = T.find(P);
  int freq = 0;
  while (pos != string::npos) {
    ++freq;
    printf("P is found at index %d in T\n", pos);
    pos = T.find(P, pos + 1);
  }
  printf("Freq: %d\n\n", freq);

  printf("Rabin-Karp, #match = ");
  RabinKarp RK(T);
  int hP = 0;
  // Calculate rolling hash of Pattern
  for (int i = 0; i < m; ++i)                    // O(n)
    hP = (hP + (ll) P[i] * RK.Pow[i]) % M;
  freq = 0;
  for (int i = 0; i <= n - m; ++i)                 // try all starting pos
    if (RK.hash_fast(i, i + m - 1) == hP) {             // a possible match
      ++freq;
      printf("P is found at index %d in T\n", i);
    }
  printf("Freq: %d\n\n", freq);

  printf("Knuth-Morris-Pratt, #match = ");
  KMP kmp(T, P);
  printf("%d\n\n", kmp.kmpSearch());

  printf("Booth's Algorithm, minimum lexicographic rotation of string starts at index ");
  printf("%d\n", least_rotation(T));

  return 0;
}
