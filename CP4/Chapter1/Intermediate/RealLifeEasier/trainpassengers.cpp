#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, n, left, entered, stay, curr = 0; cin >> c >> n;
    while (n--) {
        cin >> left >> entered >> stay;
        curr -= left;
        if (curr < 0) {
            cout << "impossible";
            return 0;
        }
        curr += entered;
        if (curr > c || stay > 0 && curr < c) {
            cout << "impossible";
            return 0;
        }
    }
    if (curr != 0) cout << "impossible";
    else cout << "possible";
}