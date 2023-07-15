#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    string s;
    vector<string> v(14);
    v[0] += "G: "; v[1] += "F: "; v[2] += "E: "; v[3] += "D: "; v[4] += "C: "; v[5] += "B: "; v[6] += "A: ";
    v[7] += "g: "; v[8] += "f: "; v[9] += "e: "; v[10] += "d: "; v[11] += "c: "; v[12] += "b: "; v[13] += "a: ";
    for (int i = 0; i < n; i++) {
        cin >> s;
        int len = 1, idx;
        if (s.size() != 1) len = stoi(s.substr(1));
        while (len-- >= 0) {
            for (int j = 0; j < 14; j++) {
                if (j == 1 || j == 3 || j == 5 || j == 7 || j == 9 || j == 13) v[j] += '-';
                else v[j] += ' ';
            }
            if (len >= 0) {
                if (islower(s[0])) idx = 13 - s[0] + 97;
                else idx = 6 - s[0] + 65;
                v[idx].pop_back(); v[idx].push_back('*');
            }
        }
    }
    for (string& str : v) {
        str.pop_back();
        cout << str << '\n';
    }
}