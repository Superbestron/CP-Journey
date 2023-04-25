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
    string date;
    unordered_set<int> others;
    int n, arr[100], diff = 0, d, month = 1; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> date >> date;
        vector<string> v = split(date, '-');
        int day = stoi(v[1]);
        // convert to days since Jan-01
        switch (stoi(v[0])) {
            case 2: day += 31; break;
            case 3: day += 59; break;
            case 4: day += 90; break;
            case 5: day += 120; break;
            case 6: day += 151; break;
            case 7: day += 181; break;
            case 8: day += 212; break;
            case 9: day += 243; break;
            case 10: day += 273; break;
            case 11: day += 304; break;
            case 12: day += 334; break;
        }
        day--;
        // convert to days since Oct-29 (so that the day before is the earliest valid date)
        arr[i] = (day + (365 - 273 - 28)) % 365;
        others.insert(arr[i]);
    }
    sort(arr, arr + n);
    // to account for missing check in for loop below
    if (365 - arr[n - 1] + arr[0] > diff && others.count(arr[0] - 1) == 0) {
        diff = 365 - arr[n - 1] + arr[0];
        d = arr[0] - 1;
    }
    for (int i = 1; i < n; i++) {
        if (arr[i] - arr[i - 1] > diff && others.count(arr[i] - 1) == 0) {
            diff = arr[i] - arr[i - 1];
            d = arr[i] - 1;
        }
    }
    // convert back to days after Jan-01
    d = (d + 273 + 28) % 365;
    d += 1;
    if (d > 334) {
        month = 12; d -= 334;
    }
    else if (d > 304) {
        month = 11; d -= 304;
    }
    else if (d > 273) {
        month = 10; d -= 273;
    }
    else if (d > 243) {
        month = 9; d -= 243;
    }
    else if (d > 212) {
        month = 8; d -= 212;
    }
    else if (d > 181) {
        month = 7; d -= 181;
    }
    else if (d > 151) {
        month = 6; d -= 151;
    }
    else if (d > 120) {
        month = 5; d -= 120;
    }
    else if (d > 90) {
        month = 4; d -= 90;
    }
    else if (d > 59) {
        month = 3; d -= 59;
    }
    else if (d > 31) {
        month = 2; d -= 31;
    } else month = 1;

    cout << string(2 - min(2, (int) to_string(month).length()), '0') + to_string(month) + '-' +
            string(2 - min(2, (int) to_string(d).length()), '0') + to_string(d);
}