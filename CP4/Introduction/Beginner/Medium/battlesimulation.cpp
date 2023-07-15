#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    string_view str(s);
    for (int i = 0; i < s.size(); i++) {
        if (i != s.size() - 2 and i != s.size() - 1) {
            string_view substr = str.substr(i, 3);
            if (substr == "RBL" or substr == "RLB" or substr == "LBR"
                or substr == "LRB" or substr == "BLR" or substr == "BRL") {
                cout << 'C';
                i += 2;
                continue;
            }
        }
        if (s[i] == 'R') cout << 'S';
        else if (s[i] == 'B') cout << 'K';
        else cout << 'H';
    }
}