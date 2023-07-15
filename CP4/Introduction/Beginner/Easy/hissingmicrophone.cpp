#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    for (int i = 1; i < s.size(); i++) {
        if (s[i - 1] == 's' && s[i] == 's') {
            cout << "hiss";
            return 0;
        }
    }
    cout << "no hiss";
}