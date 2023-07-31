#include <bits/stdc++.h>

using namespace std;

string T;                         // T = text, P = pattern
typedef long long ll;

int n;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int>& v) const {
        return v.first * 31 + v.second;
    }
};

// Always use 2 hashes to avoid collisions
// Rabin-Karp's algorithm specific code

const int p1 = 131;                               // p and M are
const int M = 1e9+7;                             // relatively prime
const int p2 = 313;                               // p and M are

vector<int> Pow1, Pow2;                              // to store p^i % M
vector<int> h;                                   // to store prefix hashes

int computeRollingHash(vector<int>& Pow) {                      // Overall: O(n)
    h[0] = 0;
    for (int i = 0; i < n; ++i) {                  // O(n)
        if (i != 0) h[i] = h[i-1];                   // rolling hash
        h[i] = (h[i] + ((ll)T[i]*Pow[i]) % M) % M;
    }
    return h[n - 1];
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

int hash_fast(int L, int R, int to_divide, vector<int>& h) {                    // O(1) hash of any substr
    if (L > R) return 0;
    if (L == 0) return h[R];                       // h is the prefix hashes
    int ans = ((h[R] - h[L-1]) % M + M) % M;           // compute differences
    ans = ((ll)ans * modInverse(to_divide, M)) % M;   // remove P[L]^-1 (mod M)
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    vector<string> v(N);
    unordered_set<pair<int, int>, pair_hash> hashes;
    vector<pair<vector<int>, vector<int>>> str_to_hash(N, pair<vector<int>, vector<int>>({{}, {}}));
    Pow1.assign( 1000000, 0);
    Pow2.assign(1000000, 0);
    Pow1[0] = 1; Pow2[0] = 1;                                    // compute p^i % M
    for (int i = 1; i < 1000000; ++i)                    // O(n)
        Pow1[i] = ((ll)Pow1[i-1]*p1) % M;
    for (int i = 1; i < 1000000; ++i)                    // O(n)
        Pow2[i] = ((ll)Pow2[i-1]*p2) % M;
    for (int i = 0; i < N; i++) {
        cin >> T;
        n = T.size();
        h.assign(n, 0);
        int hash1 = computeRollingHash(Pow1);
        str_to_hash[i].first = std::move(h);
        h.assign(n, 0);
        int hash2 = computeRollingHash(Pow2);
        str_to_hash[i].second = std::move(h);
        hashes.emplace(hash1, hash2);
        v[i] = std::move(T);
    }
    bool typos = false;
    for (int j = 0; j < v.size(); j++) {
        auto& str = v[j];
        bool found = false;
        for (int i = 0; i < str.size(); i++) {
            int temp1 = (hash_fast(0, i - 1, 1, str_to_hash[j].first) + hash_fast(i + 1, str.size() - 1, p1, str_to_hash[j].first)) % M;
            int temp2 = (hash_fast(0, i - 1, 1, str_to_hash[j].second) + hash_fast(i + 1, str.size() - 1, p2, str_to_hash[j].second)) % M;
            if (hashes.count(make_pair(temp1, temp2))) {
                found = true;
                break;
            }
        }
        if (found) {
            typos = true;
            cout << str << '\n';
        }
    }
    if (!typos) cout << "NO TYPOS\n";
}