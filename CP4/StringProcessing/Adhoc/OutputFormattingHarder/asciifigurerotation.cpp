#include <bits/stdc++.h>
using namespace std;

static inline string& rtrim(string& s) {
    s.erase(find_if_not(s.rbegin(), s.rend(), [](int c) {return isspace(c); }).base(), s.end());
    return s;
}

int main() {
    int n;
    string line;
    bool first = true;
    while (cin >> n && n != 0) {
        cin.ignore();
        int max_col = 0;
        if (!first)
            cout << endl;
        vector<string> figure;
        for (int i = 0; i < n; i++) {
            getline(cin, line);
            figure.push_back(line);
            max_col = max(max_col, (int) line.size());
        }

        vector<vector<char>> rotation(max_col, vector<char>(n, ' '));
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < figure[r].size(); c++) {
                if (figure[r][c] == '|')
                    rotation[c][r] = '-';
                else if (figure[r][c] == '-')
                    rotation[c][r] = '|';
                else
                    rotation[c][r] = figure[r][c];
            }
        }

        for (int r = 0; r < max_col; r++) {
            string out;
            for (int c = n - 1; c >= 0; c--) {
                out += rotation[r][c];
            }
            string res = rtrim(out);
            if (!res.empty())
                cout << res << endl;
        }
        first = false;
    }
}