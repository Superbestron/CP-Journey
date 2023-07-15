#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    unordered_map<string, float> m;
    m["UTC"] = m["GMT"] = m["WET"] = 0;
    m["BST"] = m["IST"] = m["WEST"] = m["CET"] = 1;
    m["CEST"] = m["EET"] = 2;
    m["EEST"] = m["MSK"] = 3;
    m["MSD"] = 4;
    m["AST"] = m["EDT"] = -4;
    m["ADT"] = -3;
    m["NST"] = -3.5;
    m["NDT"] = -2.5;
    m["EST"] = m["CDT"] = -5;
    m["CST"] = m["MDT"] = -6;
    m["MST"] = m["PDT"]= -7;
    m["PST"] = m["AKDT"] = -8;
    m["HST"] = -10;
    m["AKST"] = -9;
    m["AEST"] = 10;
    m["AEDT"] = 11;
    m["ACST"] = 9.5;
    m["ACDT"] = 10.5;
    m["AWST"] = 8;
    while (N--) {
        string time, morn, first, second;
        cin >> time;
        if (time == "noon") {
            time = "12:00";
            morn = "p.m.";
            cin >> first >> second;
        } else if (time == "midnight") {
            time = "12:00";
            morn = "a.m.";
            cin >> first >> second;
        } else {
            cin >> morn >> first >> second;
        }
        float diff = m[second] - m[first];
        if (time.size() == 4) time = "0" + time; // pad with zeroes if hour < 10
        int hour = stoi(time.substr(0, 2));
        int min = stoi(time.substr(3, 2));
        if (hour == 12 && morn == "a.m.") hour = 0;
        else if (morn == "p.m.") {
            if (hour != 12) { // make sure 12pm stays as 1200
                hour += 12;
            }
        }
        if (diff < 0) diff += 24; // so now we only have to deal with adding time
        if (floorf(diff) != diff) {
            if (min >= 30) hour++;
            min = (min + 30) % 60;
        }
        hour = (hour + (int) diff) % 24;
        if (hour == 0) {
            if (min == 0) cout << "midnight\n";
            else {
                cout << "12:";
                cout << setfill('0') << setw(2) << min;
                cout << ' ' << "a.m." << '\n';
            }
        }
        else if (hour == 12) {
            if (min == 0) cout << "noon\n";
            else {
                cout << "12:";
                cout << setfill('0') << setw(2) << min;
                cout << ' ' << "p.m." << '\n';
            }
        }
        else {
            if (hour > 12) {
                hour -= 12;
                morn = "p.m.";
            } else {
                morn = "a.m.";
            }
            cout << hour << ':';
            cout << setfill('0') << setw(2) << min;
            cout << ' ' << morn << '\n';
        }
    }
}