#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, val;
    stack<int> s;
    cin >> n;
    while (n-- > 0) {
        cin >> val;
        if (!s.empty() && (s.top() + val) % 2 == 0) {
            s.pop();
        } else {
            s.push(val);
        }
    }
    cout << s.size();
}