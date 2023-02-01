#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string row;
    vector<string> black, white;
    for (int i = 1; i <= 8; i++) {
        cin >> row >> row;
        for (int j = 2; j < 33; j += 4) {
            string pos;
            // skip empty spaces
            if (!isupper(row[j]) && !islower(row[j])) continue;
            if (row[j] != 'p' && row[j] != 'P') pos += static_cast<char>(row[j]);
            pos += (j / 4) + 'a';
            pos += (9 - i) + '0';
            if (isupper(row[j])) {
                white.emplace_back(pos);
            } else {
                if (pos.size() == 3) pos[0] -= 32;
                black.emplace_back(pos);
            }
        }
    }
    bool is_black = true;
    auto cmp = [&](auto& s1, auto& s2) {
        char c1 = toupper(s1[0]);
        char c2 = toupper(s2[0]);
        if (s1.size() == 3 && s2.size() == 3) {
            if (c1 == c2) {
                if (s1.back() == s2.back()) return s1 < s2;
                if (is_black) return s1.back() > s2.back();
                return s1.back() < s2.back();
            }

            if (c1 == 'K') return true;
            else if (c2 == 'K') return false;
            if (c1 == 'Q') return true;
            else if (c2 == 'Q') return false;
            if (c1 == 'R') return true;
            else if (c2 == 'R') return false;
            if (c1 == 'B') return true;
            else if (c2 == 'B') return false;
            if (c1 == 'N') return true;
            else if (c2 == 'N') return false;
            return false;
        } else if (s1.size() == 2 && s2.size() == 2) {
            if (s1.back() == s2.back()) return s1 < s2;
            if (is_black) return s1.back() > s2.back();
            return s1.back() < s2.back();
        } else return s1.size() > s2.size();
    };
    sort(black.begin(), black.end(), cmp);
    is_black = false;
    sort(white.begin(), white.end(), cmp);
    cout << "White: ";
    bool first = false;
    for (string& s : white) {
        if (first) cout << ',';
        else first = true;
        cout << s;
    }
    cout << "\nBlack: ";
    first = false;
    for (string& s : black) {
        if (first) cout << ',';
        else first = true;
        cout << s;
    }
    cout << '\n';
}