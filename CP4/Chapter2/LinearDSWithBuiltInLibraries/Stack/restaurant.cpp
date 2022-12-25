#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, val, s1, s2;
    string command;
    cin >> n;
    while (n != 0) {
        s1 = 0, s2 = 0;
        for (int i = 0; i < n; i++) {
            cin >> command >> val;
            if (command == "DROP") {
                // always make sure to deposit on pile with plates
                s2 += val; // assume will never bao
                cout << "DROP 2 " << val << endl;
            } else {
                if (s1 >= val) {
                    cout << "TAKE 1 " << val << endl;
                    s1 -= val;
                } else {
                    if (s1 != 0) {
                        cout << "TAKE 1 " << s1 << endl;
                        val -= s1;
                    }
                    cout << "MOVE 2->1 " << s2 << endl;
                    cout << "TAKE 1 " << val << endl;
                    s1 = s2 - val;
                    s2 = 0;
                }
            }
        }
        cin >> n;
        cout << endl;
    }
}