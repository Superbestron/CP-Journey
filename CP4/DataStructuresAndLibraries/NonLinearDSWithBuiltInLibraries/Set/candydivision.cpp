#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n; cin >> n;
    vector<long long> v; // temp storage to store second half of divisors
    for (long long i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            cout << i - 1 << ' ';
            if (n / i != i) v.push_back(n / i);
        }
    }
    for (auto i = v.size(); i > 0; i--) cout << v[i - 1] - 1 << ' ';
}
