#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
const int mod = 1e9 + 7;

long long fexp(long long b, long long p, long long mod){
    if (p == 0) return 1;
    if (p == 1) return b;

    if (p & 1) {
        return (((fexp(b, p >> 1, mod) * fexp(b, p >> 1, mod)) % mod) * b) % mod;
    } else{
        return (fexp(b, p >> 1, mod) * fexp(b, p >> 1, mod)) % mod;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long T, d; cin >> T;
    while (T--) {
        cin >> d;
        cout << (8 * fexp(9, d - 1, mod)) % mod << '\n';
    }
}