#include <bits/stdc++.h>

using namespace std;

vector<string> v;

string plus___plus() {
    return "+---+  ";
}

string _plus() {
    return "    +  ";
}

string plus_plus() {
    return "+   +  ";
}

string plus____() {
    return "+      ";
}

string x____() {
    return "|      ";
}

string ____x() {
    return "    |  ";
}

string ____plus() {
    return "    +  ";
}

string x___x() {
    return "|   |  ";
}

void output(char c) {
    if (c == '1') {
        v[0] += ____plus(); v[1] += ____x(); v[2] += ____x(); v[3] += ____plus();
        v[4] += ____x(); v[5] += ____x(); v[6] += ____plus();
    } else if (c == '2') {
        v[0] += plus___plus(); v[1] += ____x(); v[2] += ____x(); v[3] += plus___plus();
        v[4] += x____(); v[5] += x____(); v[6] += plus___plus();
    } else if (c == '3') {
        v[0] += plus___plus(); v[1] += ____x(); v[2] += ____x(); v[3] += plus___plus();
        v[4] += ____x(); v[5] += ____x(); v[6] += plus___plus();
    } else if (c == '4') {
        v[0] += plus_plus(); v[1] += x___x(); v[2] += x___x(); v[3] += plus___plus();
        v[4] += ____x(); v[5] += ____x(); v[6] += _plus();
    } else if (c == '5') {
        v[0] += plus___plus(); v[1] += x____(); v[2] += x____(); v[3] += plus___plus();
        v[4] += ____x(); v[5] += ____x(); v[6] += plus___plus();
    } else if (c == '6') {
        v[0] += plus___plus(); v[1] += x____(); v[2] += x____(); v[3] += plus___plus();
        v[4] += x___x(); v[5] += x___x(); v[6] += plus___plus();
    } else if (c == '7') {
        v[0] += plus___plus(); v[1] += ____x(); v[2] += ____x(); v[3] += ____plus();
        v[4] += ____x(); v[5] += ____x(); v[6] += ____plus();
    } else if (c == '8') {
        v[0] += plus___plus(); v[1] += x___x(); v[2] += x___x(); v[3] += plus___plus();
        v[4] += x___x(); v[5] += x___x(); v[6] += plus___plus();
    } else if (c == '9') {
        v[0] += plus___plus(); v[1] += x___x(); v[2] += x___x(); v[3] += plus___plus();
        v[4] += ____x(); v[5] += ____x(); v[6] += plus___plus();
    } else if (c == '0') {
        v[0] += plus___plus(); v[1] += x___x(); v[2] += x___x(); v[3] += plus_plus();
        v[4] += x___x(); v[5] += x___x(); v[6] += plus___plus();
    } else {
        v[0] += "   "; v[1] += "   "; v[2] += "o  "; v[3] += "   "; v[4] += "o  ";
        v[5] += "   "; v[6] += "   ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s && s != "end") {
        v = vector<string>(7, "");
        for (char c : s) {
            output(c);
        }
        for (string& str : v) cout << str.substr(0, str.size() - 2) << '\n';
        cout << '\n' << '\n';
    }
    cout << "end" << '\n';
}
