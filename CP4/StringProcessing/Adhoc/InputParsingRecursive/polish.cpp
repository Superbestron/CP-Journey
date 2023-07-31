#include <bits/stdc++.h>

using namespace std;

vector<string> v;
unordered_set<string> ops = {"*", "+", "-"};

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

string parse(int l, int r) {
    if (l == r) return v[l];
    int num_vals = 0, num_ops = 0, left_end = -1;
    for (int i = l + 1; i < r; i++) {
        if (ops.count(v[i])) num_ops++;
        else num_vals++;
        if (num_ops + 1 == num_vals) {
            left_end = i;
            break;
        }
    }
    string left = parse(l + 1, left_end);
    string right = parse(left_end + 1, r);

    bool is_left_num = false, is_right_num = false;
    try {
        stoi(left);
        is_left_num = true;
    } catch(...) {}
    try {
        stoi(right);
        is_right_num = true;
    } catch(...) {}
    if (is_left_num && is_right_num) {
        if (v[l] == "+") return to_string(stoi(left) + stoi(right));
        else if (v[l] == "-") return to_string(stoi(left) - stoi(right));
        else return to_string(stoi(left) * stoi(right));
    } else return v[l] + ' ' + left + ' ' + right;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int tc = 1;
    while (getline(cin, s)) {
        v = split(s, ' ');
        cout << "Case " << tc++ << ": " << parse(0, v.size() - 1) << '\n';
    }
}