#include <bits/stdc++.h>

using namespace std;

vector<string> split(string s, char delimiter) {
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
    string start, end;
    cin >> start >> end;
    if (start == end) {
        cout << "24:00:00";
        return 0;
    }
    vector<string> s1 = split(start, ':'), s2 = split(end, ':');
    int start_sec = stoi(s1[0]) * 3600 + stoi(s1[1]) * 60 + stoi(s1[2]);
    int end_sec = stoi(s2[0]) * 3600 + stoi(s2[1]) * 60 + stoi(s2[2]);
    int diff_sec = (end_sec + 3600 * 24 - start_sec) % (3600 * 24);
    int hours = diff_sec / 3600, mins = (diff_sec - hours * 3600) / 60,
            secs = diff_sec - hours * 3600 - mins * 60;
    cout << string(2 - min(2, (int) to_string(hours).length()), '0') + to_string(hours)
    + ':' + string(2 - min(2, (int) to_string(mins).length()), '0') + to_string(mins)
    + ':' + string(2 - min(2, (int) to_string(secs).length()), '0') + to_string(secs);
}