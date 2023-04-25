#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int T, N;
    cin >> T;
    string encoding, s;
    for (int t = 1; t <= T; t++) {
        unordered_map<char, string> m;
        unordered_set<string> set;
        bool collide = false;
        for (int i = 'A'; i <= 'Z'; i++) {
            cin >> encoding;
            m[i] = encoding;
        }
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> s;
            string temp;
            for (char c : s) {
                temp += m[c];
            }
            if (set.count(temp) == 1) collide = true;
            set.insert(temp);
        }
        cout << "Case #" << t << ": " << (collide ? "YES" : "NO") << '\n';
    }
}

