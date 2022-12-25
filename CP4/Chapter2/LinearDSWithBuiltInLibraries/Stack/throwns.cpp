#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, curr = 0;
    string val;
    stack<int> s;
    s.push(curr);
    cin >> n >> k;

    while (k-- > 0) {
        cin >> val;
        if (val == "undo") {
            cin >> val;
            int cnt = stoi(val);
            while (cnt-- > 0) {
                s.pop();
                curr = s.top();
            }
        } else {
            curr = (curr + stoi(val) + (n * 10000)) % n;
            s.push(curr);
        }
    }
    cout << curr;
}