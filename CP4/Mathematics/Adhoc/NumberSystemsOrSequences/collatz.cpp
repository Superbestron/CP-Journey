#include <bits/stdc++.h>

using namespace std;

inline long long collatz(long long i) {
    if (i % 2) return 3 * i + 1;
    else return i / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int A, B;
    while (cin >> A >> B && !(A == 0 && B == 0)) {
        unordered_map<long long, long long> m;
        long long a = A, b = B;
        m[a] = 0;
        int ctr = 1;
        while (a != 1) {
            a = collatz(a);
            m[a] = ctr;
            ctr++;
        }
        ctr = 0;
        while (!m.count(b)) {
            b = collatz(b);
            ctr++;
        }
        cout << A << " needs " << m[b] << " steps, " << B << " needs " << ctr << " steps, they meet at " << b << '\n';
    }
}