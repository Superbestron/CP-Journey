#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, op1, op2;
    string op;
    cin >> n;
    while (n != 0) {
        string ans = "????????????????????????????????";
        while (n-- > 0) {
            cin >> op;
            if (op == "CLEAR") {
                cin >> op1;
                ans[31 - op1] = '0';
            } else if (op == "SET") {
                cin >> op1;
                ans[31 - op1] = '1';
            } else if (op == "OR") {
                cin >> op1 >> op2;
                if (ans[31 - op2] == '1' || ans[31 - op1] == '1') {
                    ans[31 - op1] = '1';
                } else if (ans[31 - op2] == '?') {
                    ans[31 - op1] = '?';
                }
            } else {
                cin >> op1 >> op2;
                if (ans[31 - op1] == '0' || ans[31 - op2] == '0') {
                    ans[31 - op1] = '0';
                } else if (ans[31 - op2] == '?') {
                    ans[31 - op1] = '?';
                }
            }
        }
        cout << ans << endl;
        cin >> n;
    }
}