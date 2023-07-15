#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string s;
    cin >> n;
    while (n-- > 0) {
        cin >> s;
        if (s == "P=NP") cout << "skipped" << endl;
        else {
            int i;
            for (i = 0; i < s.size(); i++) if (s[i] == '+') break;
            int x, y;
            x = stoi(s.substr(0, i));
            y = stoi(s.substr(i));
            cout << x + y << endl;
        }
    }
}