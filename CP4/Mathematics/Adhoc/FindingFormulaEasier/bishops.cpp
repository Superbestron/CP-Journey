#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        if (n == 1) cout << n << endl;
        else cout << (n - 1) * 2 << endl;
    }
}
