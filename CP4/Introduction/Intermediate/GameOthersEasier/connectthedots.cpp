#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (!cin.eof()) {
        vector<string> v; vector<char> seq;
        unordered_map<char, pair<int, int>> m;
        while (getline(cin, s) && !s.empty()) {
            v.emplace_back(s);
        }
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[0].size(); j++) {
                if (v[i][j] != '.') {
                    seq.push_back(v[i][j]);
                    m[v[i][j]] = make_pair(i, j);
                }
            }
        }

        auto comparator = [](char c1, char c2) {
            if (islower(c1)) {
                if (isupper(c2)) return true;
            } else if (islower(c2)) {
                if (isupper(c1)) return false;
            }
            return c1 < c2;
        };

        sort(seq.begin(), seq.end(), comparator);
        for (int i = 0; i < static_cast<int>(seq.size()) - 1; i++) {
            char src = seq[i], dest = seq[i + 1];
            // settle vertical coord
            for (int j = min(m[src].first, m[dest].first) + 1; j < max(m[src].first, m[dest].first); j++) {
                if (v[j][m[src].second] == '-') v[j][m[src].second] = '+';
                else if (v[j][m[src].second] == '.') v[j][m[src].second] = '|';
            }
            // settle horizontal coord
            for (int j = min(m[src].second, m[dest].second) + 1; j < max(m[src].second, m[dest].second); j++) {
                if (v[m[dest].first][j] == '|') v[m[dest].first][j] = '+';
                else if (v[m[dest].first][j] == '.') v[m[dest].first][j] = '-';
            }
        }
        for (auto& str : v) {
            cout << str << endl;
        }
        cout << endl;
    }
}