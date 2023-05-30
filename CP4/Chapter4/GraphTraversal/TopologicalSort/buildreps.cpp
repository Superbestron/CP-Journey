#include <bits/stdc++.h>

using namespace std;

enum Indicators { VISITED = 0, UNVISITED = -1 };
vector<string> ts;
unordered_map<string, int> dfs_num;
unordered_map<string, unordered_set<string>> AL;

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

void toposort(const string& u) {
    dfs_num[u] = VISITED;
    for (auto& v : AL[u]) {
        if (dfs_num[v] == UNVISITED) toposort(v);
    }
    ts.push_back(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n; cin.ignore();
    string s;
    for (int i = 0; i < n; i++) {
        getline(cin, s);
        vector<string> v = split(s, ' ');
        string& source = v[0];
        v[0].pop_back();
        dfs_num[source] = UNVISITED;
        for (int j = 1; j < v.size(); j++) {
            AL[v[j]].insert(source);
        }
    }
    cin >> s;
    toposort(s);
    reverse(ts.begin(), ts.end());
    for (auto& str : ts) cout << str << '\n';
}
