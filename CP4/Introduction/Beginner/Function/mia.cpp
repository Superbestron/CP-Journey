#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int s0, s1, r0, r1;
    while (cin >> s0 >> s1 >> r0 >> r1 && (s0 != 0 || s1 != 0 && r0 != 0 && r1 != 0)) {
        int p1 = max(10 * s0 + s1, 10 * s1 + s0);
        int p2 = max(10 * r0 + r1, 10 * r1 + r0);
        if (p1 == 21) {
            if (p2 == 21) cout << "Tie.";
            else cout << "Player 1 wins.";
        } else if (p2 == 21) {
            cout << "Player 2 wins.";
        } else if (s0 == s1) {
            if (r0 == r1) {
                if (p1 > p2) cout << "Player 1 wins.";
                else if (p1 < p2) cout << "Player 2 wins.";
                else cout << "Tie.";
            } else {
                cout << "Player 1 wins.";
            }
        } else if (r0 == r1) {
            cout << "Player 2 wins.";
        } else {
            if (p1 > p2) cout << "Player 1 wins.";
            else if (p1 < p2) cout << "Player 2 wins.";
            else cout << "Tie.";
        }
        cout << endl;
    }
}