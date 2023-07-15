#include <iostream>
#include <vector>
#include <stack>

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
    string str;
    int n, min_changes = 999;
    getline(cin, str);
    cin >> n; cin.ignore();
    string strings[n];
    vector<vector<string>> v;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        getline(cin, str);
        strings[i] = str;
        v.emplace_back(split(str, ","));
    }

    // Key observation here is to choose the one that minimises
    // changes for each string, as compared to the other strings
    for (int i = 0; i < n; i++) {
        int max_changes = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int count = 0;
                for (int k = 0; k < v[0].size(); k++) {
                    if (v[i][k] != v[j][k]) count++;
                }
                max_changes = max(max_changes, count);
            }
        }
        if (min_changes > max_changes) {
            min_changes = max_changes;
            ans.clear(); ans.push_back(i);
        } else if (min_changes == max_changes) ans.push_back(i);
    }
    for (int i : ans) cout << strings[i] << endl;
}
