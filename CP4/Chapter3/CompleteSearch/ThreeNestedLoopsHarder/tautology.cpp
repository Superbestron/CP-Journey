#include <bits/stdc++.h>

using namespace std;

// use bits to speed up computation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string str;
    stack<bool> s;
    unordered_map<char, int> m;
    m['p'] = 0;
    m['q'] = 1;
    m['r'] = 2;
    m['s'] = 3;
    m['t'] = 4;
    while (cin >> str && str != "0") {
        bool taut = true;
        for (int i = 0; i < 32; i++) {
            for (int j = str.size() - 1; j >= 0; j--) {
                if (str[j] == 'p' || str[j] == 'q' || str[j] == 'r' || str[j] == 's' || str[j] == 't') {
                    s.push((i & (1 << m[str[j]])) == (1 << m[str[j]]));
                } else if (str[j] == 'K') {
                    int first = s.top(); s.pop();
                    int second = s.top(); s.pop();
                    s.push(first && second);
                } else if (str[j] == 'A') {
                    int first = s.top(); s.pop();
                    int second = s.top(); s.pop();
                    s.push(first || second);
                } else if (str[j] == 'N') {
                    int first = s.top(); s.pop();
                    s.push(!first);
                } else if (str[j] == 'C') {
                    int first = s.top(); s.pop();
                    int second = s.top(); s.pop();
                    s.push(first || !second);
                } else {
                    int first = s.top(); s.pop();
                    int second = s.top(); s.pop();
                    s.push(first == second);
                }
            }
            int ans = s.top(); s.pop();
            if (!ans) {
                taut = false;
                break;
            }
        }
        if (taut) cout << "tautology\n";
        else cout << "not\n";
    }
}
