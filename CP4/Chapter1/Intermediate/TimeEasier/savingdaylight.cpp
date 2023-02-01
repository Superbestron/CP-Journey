#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, month, date, year, st, et;
    int start_h, end_h, start_m, end_m;
    while (getline(cin, s)) {
        istringstream parse(s);
        parse >> month >> date >> year >> st >> et;
        cout << month << ' ' << date << ' ' << year << ' ';
        start_h = stoi(st.substr(0, st.find(':')));
        start_m = stoi(st.substr(st.find(':') + 1, 2));
        end_h = stoi(et.substr(0, et.find(':')));
        end_m = stoi(et.substr(et.find(':') + 1, 2));
        cout << (end_m < start_m ? end_h - start_h - 1 : end_h - start_h) << " hours ";
        cout << (end_m < start_m ? 60 - (start_m - end_m) : end_m - start_m) << " minutes" << '\n';
    }
}