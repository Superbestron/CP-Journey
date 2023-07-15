#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int h, idx = 1; string s; cin >> h >> s;
    for (char c : s) {
        if (c == 'L') idx *= 2;
        else idx = 2 * idx + 1;
    }
    cout << static_cast<int>(pow(2, h + 1)) - idx;
}