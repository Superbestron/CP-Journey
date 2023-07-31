#include <bits/stdc++.h>

using namespace std;

string arr[4];
bool visited[4][4];
int directions[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

bool dfs(string& target, int depth, int x, int y) {
    if (depth == target.size()) return true;
    for (auto& direction : directions) {
        int new_x = x + direction[0];
        int new_y = y + direction[1];
        if (new_x < 0 || new_x == 4 || new_y < 0 || new_y == 4 || visited[new_x][new_y]) continue;
        if (arr[new_x][new_y] == target[depth]) {
            visited[new_x][new_y] = true;
            if (dfs(target, depth + 1, new_x, new_y)) {
                visited[new_x][new_y] = false;
                return true;
            }
            visited[new_x][new_y] = false;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int w, b;
    cin >> w;
    vector<string> words(w);
    for (int i = 0; i < w; i++) cin >> words[i];
    cin >> b;
    memset(visited, false, sizeof visited);
    for (int i = 0; i < b; i++) {
        for (auto& j : arr) cin >> j;
        int points = 0, longest_word_size = 0, words_found = 0;
        string longest_word;
        for (auto& word : words) {
            bool find = false;
            for (int j = 0; !find && j < 4; j++) {
                for (int k = 0; !find && k < 4; k++) {
                    if (arr[j][k] == word[0]) {
                        visited[j][k] = true;
                        find = dfs(word, 1, j, k);
                        visited[j][k] = false;
                    }
                }
            }
            if (find) {
                int n = word.size();
                if (n == 3 || n == 4) points++;
                else if (n == 5) points += 2;
                else if (n == 6) points += 3;
                else if (n == 7) points += 5;
                else if (n == 8) points += 11;
                if (n > longest_word_size) {
                    longest_word_size = n;
                    longest_word = word;
                } else if (n == longest_word_size) longest_word = min(longest_word, word);
                words_found++;
            }
        }
        cout << points << ' ' << longest_word << ' ' << words_found << '\n';
    }
}