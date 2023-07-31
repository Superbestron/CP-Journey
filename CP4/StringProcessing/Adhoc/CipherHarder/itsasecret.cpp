#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    vector<vector<char>> arr(5, vector<char>(5));
    string key, word;
    while (cin >> n && n != 0) {
        cin.ignore();
        getline(cin, key);
        transform(key.begin(), key.end(), key.begin(), ::toupper);
        unordered_set<char> used = {'J'};
        unordered_map<char, pair<int, int>> coord;
        int ctr = 0;
        string stripped;
        for (char j : key) {
            if (j == ' ') continue;
            if (j == 'J') j = 'I';
            stripped += j;
        }
        key = std::move(stripped);
        for (char i : key) {
            if (used.count(i)) continue;
            arr[ctr / 5][ctr % 5] = i;
            coord[i] = make_pair(ctr / 5, ctr % 5);
            used.insert(i);
            ctr++;
        }
        for (int ltr = 'A'; ctr < 25; ltr++) {
            if (used.count(ltr)) continue;
            arr[ctr / 5][ctr % 5] = ltr;
            coord[ltr] = make_pair(ctr / 5, ctr % 5);
            ctr++;
        }
        for (int i = 0; i < n; i++) {
            string stripped;
            getline(cin, key);
            transform(key.begin(), key.end(), key.begin(), ::toupper);
            for (char j : key) {
                if (j == ' ') continue;
                if (j == 'J') j = 'I';
                stripped += j;
            }
            key.clear();
            int j = 0;
            bool just_added = false;
            char first, second;
            while (j < stripped.size()) {
                if (!just_added) {
                    first = stripped[j++];
                    key += first;
                }
                just_added = false;
                if (j == stripped.size()) {
                    assert(key.size() % 2);
                    key += 'X';
                    break;
                }
                second = stripped[j];
                if (first == second) {
                    just_added = true;
                    key += 'X';
                }
                key += second;
                j++;
            }
            string ans;
            if (key.size() % 2) key += 'X';
            for (int k = 0; k < key.size(); k += 2) {
                if (key[k] == key[k + 1] && key[k] == 'X') {
                    ans += "YY";
                    continue;
                }
                pair<int, int>& f = coord[key[k]];
                pair<int, int>& s = coord[key[k + 1]];
                if (f.first == s.first) {
                    ans += arr[f.first][(f.second + 1) % 5];
                    ans += arr[f.first][(s.second + 1) % 5];
                } else if (f.second == s.second) {
                    ans += arr[(f.first + 1) % 5][f.second];
                    ans += arr[(s.first + 1) % 5][f.second];
                } else {
                    ans += arr[f.first][s.second];
                    ans += arr[s.first][f.second];
                }
            }
            cout << ans << '\n';
        }
        cout << '\n';
    }
}