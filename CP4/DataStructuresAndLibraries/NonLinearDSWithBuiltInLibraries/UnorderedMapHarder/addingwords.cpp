#include <bits/stdc++.h>

using namespace std;

vector<string> split(string s, const string& delimiter) {
    size_t pos;
    string token;
    vector<string> arr;
    if (s.empty()) return arr;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        arr.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    arr.emplace_back(s);
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    unordered_map<string, int> m;
    unordered_map<int, string> r_m;
    while (getline(cin, s)) {
        vector<string> splitted = split(s, " ");
        if (splitted[0] == "def") {
            if (m.count(splitted[1])) {
                r_m.erase(m[splitted[1]]);
                m.erase(splitted[1]);
            }
            m[splitted[1]] = stoi(splitted[2]);
            r_m[stoi(splitted[2])] = splitted[1];
        } else if (splitted[0] == "calc") {
            int start_val;
            cout << s.substr(5, s.size() - 5);
            if (!m.count(splitted[1])) goto end;
            start_val = m[splitted[1]];
            for (int i = 2; i + 1 < splitted.size(); i += 2) {
                if (!m.count(splitted[i + 1])) goto end;
                if (splitted[i] == "+") start_val += m[splitted[i + 1]];
                else start_val -= m[splitted[i + 1]];
            }
            if (r_m.count(start_val)) {
                cout << ' ' << r_m[start_val] << endl;
                continue;
            }
            end:
            cout << " unknown" << endl;
        } else {
            m.clear(); r_m.clear();
        }
    }
}