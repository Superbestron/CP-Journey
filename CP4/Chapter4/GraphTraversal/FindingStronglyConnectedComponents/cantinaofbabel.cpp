#include <bits/stdc++.h>

using namespace std;

enum { UNVISITED = 0, VISITED = 1 };

vector<vector<int>> AL, AL_T;
vector<int> S, dfs_num;
unordered_map<string, int> person_to_int;
unordered_map<string, vector<string>> can_speak, can_understand;
int N, person_ctr = 0, num_scc = 0, scc_size;

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

inline void add_to_map(string& person) {
    if (person_to_int.count(person) == 0) {
        person_to_int[person] = person_ctr++;
    }
}

void kosaraju(int u, int pass) {
    dfs_num[u] = VISITED;
    vector<int>& neighbours = (pass == 1) ? AL[u] : AL_T[u];
    for (auto& v : neighbours) {
        if (dfs_num[v] == UNVISITED) kosaraju(v, pass);
    }
    if (pass == 1) S.push_back(u);
    else scc_size++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> N; cin.ignore();
    while (N--) {
        getline(cin, s);
        vector<string> v = split(s, ' ');
        string& name = v[0], know = v[1];
        add_to_map(name);
        can_speak[know].push_back(name);
        for (int i = 1; i < v.size(); i++) can_understand[v[i]].push_back(name);
    }
    AL.assign(person_ctr, vector<int>());
    AL_T.assign(person_ctr, vector<int>());
    for (auto& [language, persons_speak] : can_speak) {
        for (auto& person_speak : persons_speak) {
            int u = person_to_int[person_speak];
            for (auto& person_understand : can_understand[language]) {
                // prevent self loops
                if (person_speak == person_understand) continue;
                AL[u].push_back(person_to_int[person_understand]);
                AL_T[person_to_int[person_understand]].push_back(u);
            }
        }
    }
    dfs_num.assign(person_ctr, UNVISITED);
    for (int u = 0; u < person_ctr; u++) {
        if (dfs_num[u] == UNVISITED) kosaraju(u, 1);
    }
    dfs_num.assign(person_ctr, UNVISITED);
    int max_scc = 0;
    for (int i = person_ctr - 1; i >= 0; i--) {
        if (dfs_num[S[i]] == UNVISITED) {
            scc_size = 0, num_scc++, kosaraju(S[i], 2);
        }
        max_scc = max(max_scc, scc_size);
    }
    cout << person_ctr - max_scc;
}