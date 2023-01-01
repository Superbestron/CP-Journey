#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    int a1 = 0, a2 = 0, a3 = 0, i;
    char prev = s[0];
    for (i = 1; i < s.size(); i++) {
        if (prev == 'D') a1++;
        else if (prev == 'U' and s[i] == 'D') a1 += 2;
        prev = 'U';
    }
    prev = s[0];
    for (i = 1; i < s.size(); i++) {
        if (prev == 'U') a2++;
        else if (prev == 'D' and s[i] == 'U') a2 += 2;
        prev = 'D';
    }
    for (i = 1; i < s.size(); i++) {
        if (s[i] != s[i - 1]) a3++;
    }
    cout << a1 << endl << a2 << endl << a3;
}