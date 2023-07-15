#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    stack<char> s;
    int n;
    cin >> n;
    string str;
    getline(cin, str);
    getline(cin, str);
    for (int i = 0; i < n; i++) {
        char c = str[i];
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        } else if (c == ')') {
            if (s.empty() || s.top() != '(') {
                cout << c << ' ' << i;
                return 0;
            }
            s.pop();
        } else if (c == ']') {
            if (s.empty() || s.top() != '[') {
                cout << c << ' ' << i;
                return 0;
            }
            s.pop();
        } else if (c == '}') {
            if (s.empty() || s.top() != '{') {
                cout << c << ' ' << i;
                return 0;
            }
            s.pop();
        }
    }
    cout << "ok so far";
}