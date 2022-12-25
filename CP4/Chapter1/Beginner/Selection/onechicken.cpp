#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    if (n <= m) {
        cout << "Dr. Chaz will have " << m - n << " " << (m - n == 1 ? "piece" : "pieces") << " of chicken left over!";
    } else {
        cout << "Dr. Chaz needs " << n - m << " more " << (n - m == 1 ? "piece" : "pieces") << " of chicken!";
    }
}