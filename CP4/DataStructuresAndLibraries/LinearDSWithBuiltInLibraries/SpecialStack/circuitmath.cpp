#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    stack<bool> s;
    int n;
    char c;
    cin >> n;
    bool arr[n];
    for (int i = 0; i < n; i++) {
        cin >> c;
        arr[i] = c == 'T';
    }
    while (cin >> c && !cin.eof()) {
        if (c == '*') {
            bool temp = s.top();
            s.pop();
            temp &= s.top();
            s.pop();
            s.push(temp);
        } else if (c == '+') {
            bool temp = s.top();
            s.pop();
            temp |= s.top();
            s.pop();
            s.push(temp);
        } else if (c == '-') {
            bool temp = s.top();
            s.pop();
            s.push(!temp);
        } else {
            s.push(arr[c - 'A']);
        }
    }
    cout << (s.top() ? 'T' : 'F');
}