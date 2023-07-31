#include <bits/stdc++.h>

using namespace std;

void displayTable(vector<vector<char>> table) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << table[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    vector<vector<char>> arr(5, vector<char>(5));
    string key, word;
    getline(cin, key);
    getline(cin, word);
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    unordered_map<char, pair<int, int>> coord;
    int ctr = 0;
    string stripped;
    for (char j : key) {
        if (j == ' ') continue;
        stripped += j;
    }
    key = std::move(stripped);
    for (char i : key) {
        if (coord.count(i)) continue;
        arr[ctr / 5][ctr % 5] = i;
        coord[i] = make_pair(ctr / 5, ctr % 5);
        ctr++;
    }
    for (int ltr = 'A'; ctr < 25; ltr++) {
        if (coord.count(ltr)) continue;
        if (ltr == 'Q') continue;
        arr[ctr / 5][ctr % 5] = ltr;
        coord[ltr] = make_pair(ctr / 5, ctr % 5);
        ctr++;
    }
//    displayTable(arr);
    stripped = "";
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    for (char j : word) {
        if (j == ' ') continue;
        stripped += j;
    }
    int j = 0;
    bool just_added = false;
    char first, second;
    word.clear();
    while (j < stripped.size()) {
        if (!just_added) {
            first = stripped[j++];
            word += first;
        }
        just_added = false;
        if (j == stripped.size()) {
            break;
        }
        second = stripped[j];
        if (first == second) {
            just_added = true;
            word += 'X';
        }
        word += second;
        j++;
    }
    string ans;
    if (word.size() % 2) word += 'X';
    for (int k = 0; k < word.size(); k += 2) {
        pair<int, int>& f = coord[word[k]];
        pair<int, int>& s = coord[word[k + 1]];
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