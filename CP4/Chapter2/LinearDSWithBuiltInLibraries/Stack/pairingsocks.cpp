#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, val, moves = 0;
    stack<int> s1, s2;
    cin >> n;
    for (int i = 0; i < 2 * n; i++) {
        cin >> val;
        s1.push(val);
    }
    while (!s1.empty() || !s2.empty()) {
        bool can = false;
        while (!s1.empty()) {
            moves++;
            s2.push(s1.top());
            s1.pop();
            while (!s1.empty() && !s2.empty() && s1.top() == s2.top()) {
                moves++;
                can = true;
                s1.pop();
                s2.pop();
            }
        }
        while (!s2.empty()) {
            moves++;
            s1.push(s2.top());
            s2.pop();
            while (!s1.empty() && !s2.empty() && s1.top() == s2.top()) {
                moves++;
                can = true;
                s1.pop();
                s2.pop();
            }
        }
        if (!can) break;
    }
    cout << (s1.empty() && s2.empty() ? to_string(moves) : "impossible");
}