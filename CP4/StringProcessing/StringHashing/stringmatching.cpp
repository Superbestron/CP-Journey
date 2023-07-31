#include <bits/stdc++.h>

using namespace std;

string T, P;                         // T = text, P = pattern
int n, m;

// Rabin-Karp's algorithm specific code
typedef long long ll;

const int p = 131;                               // p and M are
const int M = 1e9+7;                             // relatively prime

vector<int> Pow;                                  // to store p^i % M
vector<int> h;                                    // to store prefix hashes

void computeRollingHash() {                      // Overall: O(n)
    Pow[0] = 1;                                    // compute p^i % M
    for (int i = 1; i < n; ++i)                    // O(n)
        Pow[i] = ((ll)Pow[i-1]*p) % M;
    h[0] = 0;
    for (int i = 0; i < n; ++i) {                  // O(n)
        if (i != 0) h[i] = h[i-1];                   // rolling hash
        h[i] = (h[i] + ((ll)T[i]*Pow[i]) % M) % M;
    }
}

int extEuclid(int a, int b, int &x, int &y) {    // pass x and y by ref
    int xx = y = 0;
    int yy = x = 1;
    while (b) {                                    // repeats until b == 0
        int q = a/b;
        tie(a, b) = tuple(b, a%b);
        tie(x, xx) = tuple(xx, x-q*xx);
        tie(y, yy) = tuple(yy, y-q*yy);
    }
    return a;                                      // returns gcd(a, b)
}

int modInverse(int b, int m) {                   // returns b^(-1) (mod m)
    int x, y;
    int d = extEuclid(b, m, x, y);                 // to get b*x + m*y == d
    if (d != 1) return -1;                         // to indicate failure
    // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
    return (x+m)%m;                                // this is the answer
}

int hash_fast(int L, int R) {                    // O(1) hash of any substr
    if (L == 0) return h[R];                       // h is the prefix hashes
    int ans = ((h[R] - h[L-1]) % M + M) % M;           // compute differences
    ans = ((ll)ans * modInverse(Pow[L], M)) % M;   // remove P[L]^-1 (mod M)
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (getline(cin, P)) {
        getline(cin, T);
        n = T.size();
        m = P.size();
        Pow.assign(n, 0);
        h.assign(n, 0);
        computeRollingHash();
        int hP = 0;
        for (int i = 0; i < m; ++i)                    // O(n)
            hP = (hP + (ll)P[i]*Pow[i]) % M;
        for (int i = 0; i <= n-m; ++i) {           // try all starting pos
            if (hash_fast(i, i + m - 1) == hP) {             // a possible match
                cout << i << ' ';
            }
        }
        cout << '\n';
    }
}