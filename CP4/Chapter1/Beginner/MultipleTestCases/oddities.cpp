#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, val;
    cin >> n;
    while (n-- > 0) {
        cin >> val;
        cout << val << " is " << (val % 2 == 0 ? "even" : "odd") << endl;
    }
}