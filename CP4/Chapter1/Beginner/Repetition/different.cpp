#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long v1, v2;
    while (cin >> v1 >> v2 && !cin.eof()) {
        cout << abs(v1 - v2) << endl;
    }
}