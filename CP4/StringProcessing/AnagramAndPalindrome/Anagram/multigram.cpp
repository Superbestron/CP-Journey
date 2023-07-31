#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    if (s.size() == 1) {
        cout << -1; return 0;
    }
    for (int i = 1; i <= s.size() / 2; i++) {
        if (s.size() % i) continue;
        string original = s.substr(0, i);
        string substr = original;
        sort(substr.begin(), substr.end());
        bool found = true;
        for (int j = i; j < s.size(); j += i) {
            string temp = s.substr(j, i);
            sort(temp.begin(), temp.end());
            if (substr != temp) {
                found = false;
                break;
            }
        }
        if (found) {
            cout << original;
            return 0;
        }
    }
    cout << -1;
}