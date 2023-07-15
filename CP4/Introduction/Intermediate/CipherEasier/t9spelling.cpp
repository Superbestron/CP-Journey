#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n; cin.ignore();
    unordered_map<char, string> m =
            {{'a', "2"}, {'b', "22"}, {'c', "222"}, {'d', "3"}, {'e', "33"},
             {'f', "333"}, {'g', "4"}, {'h', "44"}, {'i', "444"}, {'j', "5"},
             {'k', "55"}, {'l', "555"}, {'m', "6"}, {'n', "66"}, {'o', "666"},
             {'p', "7"}, {'q', "77"}, {'r', "777"}, {'s', "7777"}, {'t', "8"},
             {'u', "88"}, {'v', "888"}, {'w', "9"}, {'x', "99"}, {'y', "999"},
             {'z', "9999"}, {' ', "0"}};
    for (int i = 1; i <= n; i++) {
        string s, ans;
        getline(cin, s);
        char prev = ' ';
        for (char j : s) {
            string curr = m[j];
            if (curr[0] == prev) ans += ' ';
            ans += curr;
            prev = curr[0];
        }
        cout << "Case #" << i << ": " << ans << '\n';
    }
}