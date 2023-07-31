#include <bits/stdc++.h>

using namespace std;

bool hasEnding(string& fullString, string& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

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
    string S, temp;
    int E, P;
    cin >> S >> E;
    cin.ignore();
    vector<string> grand;
    for (int i = 0; i < E; i++) {
        getline(cin, temp);
        vector<string> v = split(temp, ' ');
        bool correct = false;
        for (auto& str : v) {
            if (hasEnding(S, str)) correct = true;
        }
        if (correct) grand.insert(grand.end(), v.begin(), v.end());
    }
    cin >> P; cin.ignore();
    for (int i = 0; i < P; i++) {
        getline(cin, temp);
        vector<string> v = split(temp, ' ');
        int size = v.size();
        string& last = v[size - 1];
        bool printed = false;
        for (auto& str : grand) {
            if (hasEnding(last, str)) {
                printed = true;
                break;
            }
        }
        if (printed) cout << "YES\n";
        else cout << "NO\n";
    }
}