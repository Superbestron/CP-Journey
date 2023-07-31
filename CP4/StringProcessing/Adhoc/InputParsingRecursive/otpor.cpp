#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    double arr[N];
    for (int i = 0; i < N; i++) cin >> arr[i];
    string s; cin >> s;
    stack<double> stk;
    // use neg numbers to represent non-numbers
    for (char c : s) {
        if (c == ')') {
            bool is_series = true;
            bool flipped = false;
            double sum = 0;
            while (stk.top() != -1) {
                if (stk.top() == -3 && !flipped) {
                    sum = 1 / sum;
                    is_series = false;
                    flipped = true;
                } else if (stk.top() != -2 && stk.top() != -3) {
                    if (is_series) sum += stk.top();
                    else sum += 1.0 / stk.top();
                }
                stk.pop();
            }
            stk.pop();
            if (is_series) stk.push(sum);
            else stk.push(1 / sum);
        } else if (c == 'R') continue;
        else if (c == '(') stk.push(-1);
        else if (c == '-') stk.push(-2);
        else if (c == '|') stk.push(-3);
        else stk.push(arr[c - '1']);
    }
    cout << fixed << setprecision(5) << stk.top();
}