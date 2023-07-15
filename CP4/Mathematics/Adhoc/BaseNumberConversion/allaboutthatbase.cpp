#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;

int value_converter(char num) {
    if (num >= 'a' && num <= 'z') return num - 'a' + 10;
    else if (num == '0') return 2;
    else return num - '0';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    string op1, op2, ans;
    char op, temp;
    while (t--) {
        cin >> op1 >> op >> op2 >> temp >> ans;
        bool found = false;
        int min_base = 1;
        for (char c : op1) min_base = max(min_base, value_converter(c));
        for (char c : op2) min_base = max(min_base, value_converter(c));
        for (char c : ans) min_base = max(min_base, value_converter(c));
        for (int i = min_base; i <= 36; i++) {
            int num1, num2, answer;
            try {
                if (i == 1) {
                    num1 = op1.size();
                    num2 = op2.size();
                    answer = ans.size();
                } else {
                    num1 = stoi(op1, nullptr, i);
                    num2 = stoi(op2, nullptr, i);
                    answer = stoi(ans, nullptr, i);
                }

            } catch (exception& e) {}

            bool valid = false;
            switch(op) {
                case '+': {
                    valid = num1 + num2 == answer;
                    break;
                }
                case '-': {
                    valid = num1 - num2 == answer;
                    break;
                }
                case '*': {
                    valid = num1 * num2 == answer;
                    break;
                }
                case '/': {
                    int temp_num = num1 / num2;
                    temp_num *= num2;
                    valid = temp_num == num1 && num1 / num2 == answer;
                    break;
                }
            }
            if (valid) {
                found = true;
                if (i >= 10 && i != 36) cout << char('a' + i - 10);
                else if (i == 36) cout << 0;
                else cout << i;
            }
        }
        if (!found) cout << "invalid";
        cout << "\n";
    }
}