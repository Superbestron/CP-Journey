#include <bits/stdc++.h>

using namespace std;

vector<string> v(7);
vector<string> ans(7);

string ____x() {
    return "....x";
}

string x____() {
    return "x....";
}

string x___x() {
    return "x...x";
}

string __x__() {
    return "..x..";
}

string xxxxx() {
    return "xxxxx";
}

char convertToChar(int idx) {
    string l1 = v[0].substr(idx, 5);
    string l2 = v[1].substr(idx, 5);
    string l3 = v[2].substr(idx, 5);
    string l4 = v[3].substr(idx, 5);
    string l5 = v[4].substr(idx, 5);
    string l6 = v[5].substr(idx, 5);
    string l7 = v[6].substr(idx, 5);
    if (l1 == ____x() && l2 == ____x() && l3 == ____x() && l4 == ____x() && l5 == ____x() && l6 == ____x() && l7 == ____x()) return '1';
    else if (l1 == xxxxx() && l2 == ____x() && l3 == ____x() && l4 == xxxxx() && l5 == x____() && l6 == x____() && l7 == xxxxx()) return '2';
    else if (l1 == xxxxx() && l2 == ____x() && l3 == ____x() && l4 == xxxxx() && l5 == ____x() && l6 == ____x() && l7 == xxxxx()) return '3';
    else if (l1 == x___x() && l2 == x___x() && l3 == x___x() && l4 == xxxxx() && l5 == ____x() && l6 == ____x() && l7 == ____x()) return '4';
    else if (l1 == xxxxx() && l2 == x____() && l3 == x____() && l4 == xxxxx() && l5 == ____x() && l6 == ____x() && l7 == xxxxx()) return '5';
    else if (l1 == xxxxx() && l2 == x____() && l3 == x____() && l4 == xxxxx() && l5 == x___x() && l6 == x___x() && l7 == xxxxx()) return '6';
    else if (l1 == xxxxx() && l2 == ____x() && l3 == ____x() && l4 == ____x() && l5 == ____x() && l6 == ____x() && l7 == ____x()) return '7';
    else if (l1 == xxxxx() && l2 == x___x() && l3 == x___x() && l4 == xxxxx() && l5 == x___x() && l6 == x___x() && l7 == xxxxx()) return '8';
    else if (l1 == xxxxx() && l2 == x___x() && l3 == x___x() && l4 == xxxxx() && l5 == ____x() && l6 == ____x() && l7 == xxxxx()) return '9';
    else if (l1 == xxxxx() && l2 == x___x() && l3 == x___x() && l4 == x___x() && l5 == x___x() && l6 == x___x() && l7 == xxxxx()) return '0';
    else return '+';
}

void convertToString(char c) {
    if (c == '1') {
        ans[0] += ____x(); ans[1] += ____x(); ans[2] += ____x(); ans[3] += ____x(); ans[4] += ____x(); ans[5] += ____x(); ans[6] += ____x();
    } else if (c == '2') {
        ans[0] += xxxxx(); ans[1] += ____x(); ans[2] += ____x(); ans[3] += xxxxx(); ans[4] += x____(); ans[5] += x____(); ans[6] += xxxxx();
    } else if (c == '3') {
        ans[0] += xxxxx(); ans[1] += ____x(); ans[2] += ____x(); ans[3] += xxxxx(); ans[4] += ____x(); ans[5] += ____x(); ans[6] += xxxxx();
    } else if (c == '4') {
        ans[0] += x___x(); ans[1] += x___x(); ans[2] += x___x(); ans[3] += xxxxx(); ans[4] += ____x(); ans[5] += ____x(); ans[6] += ____x();
    } else if (c == '5') {
        ans[0] += xxxxx(); ans[1] += x____(); ans[2] += x____(); ans[3] += xxxxx(); ans[4] += ____x(); ans[5] += ____x(); ans[6] += xxxxx();
    } else if (c == '6') {
        ans[0] += xxxxx(); ans[1] += x____(); ans[2] += x____(); ans[3] += xxxxx(); ans[4] += x___x(); ans[5] += x___x(); ans[6] += xxxxx();
    } else if (c == '7') {
        ans[0] += xxxxx(); ans[1] += ____x(); ans[2] += ____x(); ans[3] += ____x(); ans[4] += ____x(); ans[5] += ____x(); ans[6] += ____x();
    } else if (c == '8') {
        ans[0] += xxxxx(); ans[1] += x___x(); ans[2] += x___x(); ans[3] += xxxxx(); ans[4] += x___x(); ans[5] += x___x(); ans[6] += xxxxx();
    } else if (c == '9') {
        ans[0] += xxxxx(); ans[1] += x___x(); ans[2] += x___x(); ans[3] += xxxxx(); ans[4] += ____x(); ans[5] += ____x(); ans[6] += xxxxx();
    } else {
        ans[0] += xxxxx(); ans[1] += x___x(); ans[2] += x___x(); ans[3] += x___x(); ans[4] += x___x(); ans[5] += x___x(); ans[6] += xxxxx();
    }
    for (string& s : ans) s += '.';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 7; i++) {
        cin >> v[i];
    }
    int ctr = 0;
    bool second = false;
    string s1, s2;
    while (ctr < v[0].size()) {
        char c = convertToChar(ctr);
        ctr += 6; // account for space
        if (c == '+') second = true;
        else if (second) s2 += c;
        else s1 += c;
    }
    string ans_str = to_string(stoi(s1) + stoi(s2));
    for (char c : ans_str) {
        convertToString(c);
    }
    for (string& str : ans) {
        str.pop_back();
        cout << str << '\n';
    }
}