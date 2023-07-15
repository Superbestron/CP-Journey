#include <bits/stdc++.h>

using namespace std;

vector<string> split(string s, const string& delimiter) {
    size_t pos;
    string token;
    vector<string> arr;
    if (s.empty()) return arr;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        arr.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    arr.emplace_back(s);
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string w, b;
    string border = "+---+---+---+---+---+---+---+---+";
    string one = "|...|:::|...|:::|...|:::|...|:::|";
    string two = "|:::|...|:::|...|:::|...|:::|...|";
    getline(cin, w);
    getline(cin, b);
    w = w.substr(7);
    b = b.substr(7);
    vector<string> black = split(b, ",");
    vector<string> white = split(w, ",");
    vector<string> ans;
    for (int i = 0; i < 4; i++) {
        ans.push_back(border);
        ans.push_back(one);
        ans.push_back(border);
        ans.push_back(two);
    }
    ans.push_back(border);
    for (int i = 0; i < white.size(); i++) {
        int row = 2 * (7 - (white[i].back() - '1')) + 1;
        int col = (white[i][white[i].size() - 2] - 'a') * 4 + 2;
        if (white[i].size() == 3) {
            ans[row][col] = white[i][0];
        } else {
            ans[row][col] = 'P';
        }
    }
    for (int i = 0; i < black.size(); i++) {
        int row = 2 * (7 - (black[i].back() - '1')) + 1;
        int col = (black[i][black[i].size() - 2] - 'a') * 4 + 2;
        if (black[i].size() == 3) {
            ans[row][col] = tolower(black[i][0]);
        } else {
            ans[row][col] = 'p';
        }
    }
    for (auto& s : ans) cout << s << '\n';
}