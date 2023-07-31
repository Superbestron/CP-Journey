#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    int freq[26], cnt = 0;
    memset(freq, 0, sizeof freq);
    for (char c : s) freq[c - 'a']++;
    for (int i : freq) {
        if (i % 2) cnt++;
    }
    if (cnt <= 1) cout << 0;
    else cout << cnt - 1;
}