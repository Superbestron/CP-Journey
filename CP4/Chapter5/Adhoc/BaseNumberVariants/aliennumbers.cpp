#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    unordered_map<char, int> source;
    unordered_map<int, char> target;
    string alien_number, source_language, target_language;
    for (int i = 1; i <= T; i++) {
        cin >> alien_number >> source_language >> target_language;
        string answer;
        int ctr = 0, base = 1, value = 0;
        int target_size = target_language.size();
        for (char c : source_language) source[c] = ctr++;
        ctr = 0;
        for (char c : target_language) target[ctr++] = c;
        for (int j = alien_number.size() - 1; j >= 0; j--) {
            value += base * source[alien_number[j]];
            base *= source_language.size();
        }
        while (value != 0) {
            int remainder = value % target_size;
            answer += target[remainder];
            value -= remainder;
            value /= target_size;
        }
        reverse(answer.begin(), answer.end());
        cout << "Case #" << i << ": " << answer << '\n';
    }
}