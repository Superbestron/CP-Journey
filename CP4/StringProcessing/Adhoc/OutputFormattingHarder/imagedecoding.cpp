#include <bits/stdc++.h>

using namespace std;

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

// Very bad checking system, any extra newline is considered WA
// Make sure don't print extra newline after the last test.txt case

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string s;
    bool first = true;
    while (cin >> n && n != 0) {
        if (!first) cout << '\n';
        cin.ignore();
        bool has_error = false;
        int num_row = -1;
        for (int i = 0; i < n; i++) {
            getline(cin, s);
            vector<string> v = split(s, ' ');
            bool is_hex = v[0] == "#";
            int num_row_curr = 0;
            for (int j = 1; j < v.size(); j++) {
                int num = stoi(v[j]);
                num_row_curr += num;
                if (is_hex) {
                    for (int k = 0; k < num; k++) cout << '#';
                    is_hex = false;
                } else {
                    for (int k = 0; k < num; k++) cout << '.';
                    is_hex = true;
                }
            }
            if (num_row == -1) num_row = num_row_curr;
            else if (num_row != num_row_curr) has_error = true;
            cout << '\n';
        }
        if (has_error) cout << "Error decoding image\n";
        first = false;
    }
}