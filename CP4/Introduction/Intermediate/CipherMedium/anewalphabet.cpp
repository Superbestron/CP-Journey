#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<char, string> m =
        {{'a', "@"}, {'b', "8"}, {'c', "("}, {'d', "|)"}, {'e', "3"},
         {'f', "#"}, {'g', "6"}, {'h', "[-]"}, {'i', "|"}, {'j', "_|"},
         {'k', "|<"}, {'l', "1"}, {'m', "[]\\/[]"}, {'n', "[]\\[]"}, {'o', "0"},
         {'p', "|D"}, {'q', "(,)"}, {'r', "|z"}, {'s', "$"}, {'t', "']['"},
         {'u', "|_|"}, {'v', "\\/"}, {'w', "\\/\\/"}, {'x', "}{"}, {'y', "`/"},
         {'z', "2"}};;
    string s, ans;
    getline(cin, s);
    for (char c : s) {
        if (isupper(c)) c += 32;
        if (m.count(c) == 1) ans += m[c];
        else ans += c;
    }
    cout << ans;
}