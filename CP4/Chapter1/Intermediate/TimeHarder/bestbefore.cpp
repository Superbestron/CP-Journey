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
    string s, ans; cin >> s;
    vector<string> v = split(s, '/');
    int arr[3] = {0, 1, 2}, mini = INT32_MAX;
    do {
        int day = stoi(v[arr[0]]);
        int month = stoi(v[arr[1]]);
        int year = stoi(v[arr[2]]);
        if (year < 2000) year += 2000;
        if (day == 0 || month == 0) continue;
        if (month > 12) continue;
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            if (day > 31) continue;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) continue;
        } else {
            bool leap;
            if (year % 400 == 0) {
                leap = true;
            } else if (year % 100 == 0) {
                leap = false;
            } else if (year % 4 == 0) {
                leap = true;
            } else {
                leap = false;
            }
            if (leap) {
                if (day > 29) continue;
            } else {
                if (day > 28) continue;
            }
        }
        int value = year * 10000 + month * 100 + day;
        if (value < mini) {
            mini = value;
            ans = string(4 - min(4, (int) to_string(year).length()), '0') + to_string(year)
                    + '-' + string(2 - min(2, (int) to_string(month).length()), '0') + to_string(month)
                    + '-' + string(2 - min(2, (int) to_string(day).length()), '0') + to_string(day);
        }
    } while (next_permutation(arr, arr + 3));
    if (ans.empty()) cout << s << " is illegal" << '\n';
    else cout << ans;
}