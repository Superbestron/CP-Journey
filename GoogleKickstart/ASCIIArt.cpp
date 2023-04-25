#include <bits/stdc++.h>

using namespace std;

long long findN(long long x) {
    long long n = 0, ans;
    do {
        n++;
        ans = n * (n + 1) / 2;
    } while (ans < x);
    return n;
}

int main() {
    ios_base::sync_with_stdio(false);
    long long T, N;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N;
        long long n = findN(ceil(N / 26.0));
        long long remainder = N - 26 * (n - 1) * n / 2;
        cout << "Case #" << t << ": " << (char) ('A' + ceil(1.0 * remainder / n) - 1) << '\n';
    }
}

