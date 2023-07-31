#include <bits/stdc++.h>

using namespace std;

string s;
set<string> strs;
int memo[1000][1000];

bool isPalDP(int l, int r) { // is s[l..r] a palindrome
    if (l == r) return true; // one character
    if (l + 1 == r) return s[l] == s[r]; // two characters
    int &ans = memo[l][r];
    if (ans != -1) return ans; // has been computed
    ans = 0;
    if (s[l] == s[r]) ans = isPalDP(l+1, r-1); // if true, recurse inside
    return ans;
}
void palDP() {
    int n = s.size();
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < n; ++i) // this is O(n^2)
        for (int j = i + 1; j < n; ++j)
            if (isPalDP(i, j)) // x O(1), so O(n^2) total
                strs.insert(s.substr(i, j - i + 1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (getline(cin, s)) {
        strs.clear();
        memset(memo, -1, sizeof memo);
        palDP();
        for (auto& str : strs) cout << str << '\n';
        cout << '\n';
    }
}