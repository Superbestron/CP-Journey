#include <bits/stdc++.h>

using namespace std;

// Main idea is to delegate the printing of a new line to the next line
// For e.g. the newline on line 1 should be printed by line 2

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, curr;
    int indentation = 0;
    cin >> s;
    bool first = true;
    for (char c : s) {
        if (c == '{') {
            if (first) {
                cout << string(indentation, ' ') << c;
                first = false;
            } else cout << '\n' << string(indentation, ' ') << c;
            indentation += 2;
        } else if (c == '}') {
            if (!curr.empty()) cout << '\n' << string(indentation, ' ') << curr;
            curr.clear();
            indentation -= 2;
            cout << '\n' << string(indentation, ' ') << c;
        } else if (c == ',') {
            if (!curr.empty()) cout << '\n' << string(indentation, ' ') << curr << c;
            else cout << c;
            curr.clear();
        } else curr += c;
    }
    cout << '\n';
}