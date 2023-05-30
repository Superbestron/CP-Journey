#include <bits/stdc++.h>

using namespace std;

string s;

long long backtrack(bool has_L, int vowel_streak, int consonant_streak, int idx) {
    if (consonant_streak == 3 || vowel_streak == 3) return 0;
    if (idx == s.size()) {
        if (has_L) return 1;
        else return 0;
    }
    long long ans = 0;
    if (s[idx] == 'C' || s[idx] == 'L') {
        ans += backtrack(has_L || s[idx] == 'L', 0, consonant_streak + 1, idx + 1);
    }
    if (s[idx] == 'V') {
        ans += backtrack(has_L, vowel_streak + 1, 0, idx + 1);
    }
    if (s[idx] == '_') {
        // if consonant but not L
        ans += 20 * backtrack(has_L, 0, consonant_streak + 1, idx + 1);
        // if L
        ans += backtrack(true, 0, consonant_streak + 1, idx + 1);
        // if vowel
        ans += 5 * backtrack(has_L, vowel_streak + 1, 0, idx + 1);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    bool has_L = false;
    cin >> s;
    for (char& c : s) {
        if (c == 'L') has_L = true;
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') c = 'V';
        else if (c == '_') continue;
        else c = 'C';
    }
    cout << backtrack(has_L, 0, 0, 0);
}