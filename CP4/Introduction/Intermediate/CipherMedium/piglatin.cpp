#include <bits/stdc++.h>

using namespace std;

bool isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (getline(cin, s)) {
        string ans, word;
        istringstream parse(s);
        while (parse >> word) {
            string temp;
            if (!isVowel(word[0])) {
                for (int i = 0; i < word.size(); i++) {
                    if (isVowel(word[i])) {
                        for (int j = i; j < word.size(); j++) {
                            ans += word[j];
                        }
                        break;
                    } else {
                        temp += word[i];
                    }
                }
                ans += temp + "ay";
            } else {
                ans += word + "yay";
            }
            ans += ' ';
        }
        cout << ans << '\n';
    }
}