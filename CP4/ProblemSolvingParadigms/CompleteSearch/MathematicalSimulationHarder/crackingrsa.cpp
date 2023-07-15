#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long T, n, e, q, d, totient; cin >> T;
    while (T--) {
        cin >> n >> e;
        for (int i = 2; i <= n; i++) {
            if (n % i == 0) {
                n /= i;
                q = i;
                break;
            }
        }
        totient = (n - 1) * (q - 1);
        d = 1;
        while (true) {
            long long x = (e * d - 1) % totient;
            if (x == 0) {
                cout << d << endl;
                break;
            }
            d++;
        }
    }
}