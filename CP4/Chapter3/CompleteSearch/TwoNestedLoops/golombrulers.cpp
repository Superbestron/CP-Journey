#include <bits/stdc++.h>

using namespace std;

vector<int> split(string s, const string& delimiter) {
    size_t pos;
    string token;
    vector<int> arr;
    if (s.empty()) return arr;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        arr.push_back(stoi(token));
        s.erase(0, pos + delimiter.length());
    }
    arr.push_back(stoi(s));
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string str;
    while (getline(cin, str)) {
        vector<int> v = split(str, " "), missing;
        unordered_set<int> s;
        int largest = 0;
        bool printed = false;
        for (int i = 0; i < v.size(); i++) {
            int val = v[i];
            largest = max(largest, val);
            for (int j = 0; j < i; j++) {
                int num = abs(v[j] - val);
                if (s.count(num)) {
                    cout << "not a ruler\n";
                    printed = true;
                    break;
                }
                s.insert(num);
            }
            if (printed) break;
        }
        if (!printed) {
            for (int i = 1; i <= largest; i++) {
                if (s.count(i) == 0) {
                    missing.push_back(i);
                }
            }
            if (missing.empty()) {
                cout << "perfect\n";
            } else {
                cout << "missing";
                for (int i : missing) cout << ' ' << i;
                cout << '\n';
            }
        }
    }
}
