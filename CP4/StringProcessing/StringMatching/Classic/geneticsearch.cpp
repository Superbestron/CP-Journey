#include <bits/stdc++.h>

using namespace std;

vector<string> split(string& s, char delimiter) {
    size_t pos;
    string token;
    vector<string> arr;
    if (s.empty()) return arr;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        arr.emplace_back(token);
        s.erase(0, pos + 1);
    }
    arr.emplace_back(s);
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (getline(cin, s) && s != "0") {
        vector<string> v = split(s, ' ');
        string& S = v[0], L = v[1];
        size_t pos = 0;
        int ans1 = 0, ans2 = 0, ans3 = 0;
        unordered_set<string> set;
        while ((pos = L.find(S, pos)) != string::npos) {
            ans1++;
            pos++;
        }
        for (int i = 0; i < S.size(); i++) {
            string copy = S;
            copy.erase(copy.begin() + i);
            if (set.count(copy)) continue;
            set.insert(copy);
            pos = 0;
            while ((pos = L.find(copy, pos)) != string::npos) {
                ans2++;
                pos++;
            }
        }
        char arr[4] = {'A', 'T', 'G', 'C'};
        for (int i = 0; i <= S.size(); i++) {
            for (char j : arr) {
                string copy = S;
                copy.insert(i, 1, j);
                if (set.count(copy)) continue;
                set.insert(copy);
                pos = 0;
                while ((pos = L.find(copy, pos)) != string::npos) {
                    ans3++;
                    pos++;
                }

            }
        }
        printf("%d %d %d\n", ans1, ans2, ans3);
    }
}