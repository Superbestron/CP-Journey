#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;

// just need to do the math in O(1) time

long double fexp(long double b, long long p){
    if (p == 0) return 1;
    if (p == 1) return b;

    if (p & 1) {
        return fexp(b, p >> 1) * fexp(b, p >> 1) * b;
    } else{
        return fexp(b, p >> 1) * fexp(b, p >> 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long double r, r_pow_n, ans;
    long long N, X, Y;
    while (cin >> X >> Y >> N >> r && !(X == 0 && Y == 0 && N == 0 && r == 0)) {
        r /= 1200;
        r += 1;
        N *= 12;
        if (r == 1) {
            if (X - Y * N < 0) cout << "YES\n";
            else cout << "NO\n";
            continue;
        }
        r_pow_n = fexp(r, N);
        ans = X * r_pow_n - Y * (r_pow_n - 1) / (r - 1);

        if (ans <= 0) cout << "YES\n";
        else cout << "NO\n";
    }
}