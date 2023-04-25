#include <bits/stdc++.h>

using namespace std;

vector<string> v;

bool is_xxx(string& x) {
    return x == "***";
}

bool is_x_x(string& x) {
    return x == "* *";
}

bool is___x(string& x) {
    return x == "  *";
}

bool is_x__(string& x) {
    return x == "*  ";
}

int checkNo(int colNow) {
    string str1 = v[0].substr(colNow, 3);
    string str2 = v[1].substr(colNow, 3);
    string str3 = v[2].substr(colNow, 3);
    string str4 = v[3].substr(colNow, 3);
    string str5 = v[4].substr(colNow, 3);
    if (is_xxx(str1) && is_x_x(str2) && is_x_x(str3) && is_x_x(str4) && is_xxx(str5)) return 0;
    else if (is___x(str1) && is___x(str2) && is___x(str3) && is___x(str4) && is___x(str5)) return 1;
    else if (is_xxx(str1) && is___x(str2) && is_xxx(str3) && is___x(str4) && is_xxx(str5)) return 3;
    else if (is_xxx(str1) && is___x(str2) && is_xxx(str3) && is_x__(str4) && is_xxx(str5)) return 2;
    else if (is_x_x(str1) && is_x_x(str2) && is_xxx(str3) && is___x(str4) && is___x(str5)) return 4;
    else if (is_xxx(str1) && is_x__(str2) && is_xxx(str3) && is___x(str4) && is_xxx(str5)) return 5;
    else if (is_xxx(str1) && is_x__(str2) && is_xxx(str3) && is_x_x(str4) && is_xxx(str5)) return 6;
    else if (is_xxx(str1) && is___x(str2) && is___x(str3) && is___x(str4) && is___x(str5)) return 7;
    else if (is_xxx(str1) && is_x_x(str2) && is_xxx(str3) && is_x_x(str4) && is_xxx(str5)) return 8;
    else if (is_xxx(str1) && is_x_x(str2) && is_xxx(str3) && is___x(str4) && is_xxx(str5)) return 9;
    else return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, ans;
    for (int i = 0; i < 5; i++) {
        getline(cin, s);
        v.emplace_back(s);
    }
    for (int i = 0; i < s.size(); i += 4) {
        int num = checkNo(i);
        if (num == -1) {
            cout << "BOOM!!";
            return 0;
        }
        ans += to_string(num);
    }
    int final = stoi(ans);
    if (final % 6) cout << "BOOM!!";
    else cout << "BEER!!";
}