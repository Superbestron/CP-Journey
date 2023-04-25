#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    auto digits_sum = [](int x) {
        int sum = 0;
        while (x != 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    };
    while (cin >> N && N != 0) {
        int p = 11, N_digits_sum = digits_sum(N);
        while (digits_sum(N * p) != N_digits_sum) {
            p++;
        }
        cout << p << '\n';
    }
}