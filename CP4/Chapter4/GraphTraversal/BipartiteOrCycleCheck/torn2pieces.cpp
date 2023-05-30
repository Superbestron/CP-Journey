#include <bits/stdc++.h>

using namespace std;

// a lot of edge cases for this question...

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, start_int, end_int, cities = 0;
    cin >> N;
    string s, src, start, end;
    unordered_map<int, unordered_set<int>> AL;
    unordered_map<string, int> name_to_int;
    unordered_map<int, string> int_to_name;
    queue<int> q;
    cin.ignore();
    for (int i = 0; i < N; i++) {
        getline(cin, s);
        vector<string> v = split(s, ' ');
        src = v[0];
        if (name_to_int.count(src) == 0) {
            name_to_int[src] = cities;
            int_to_name[cities++] = src;
        }
        for (int j = 1; j < v.size(); j++) {
            if (name_to_int.count(v[j]) == 0) {
                name_to_int[v[j]] = cities;
                int_to_name[cities++] = v[j];
            }
            AL[name_to_int[v[j]]].insert(name_to_int[src]);
            AL[name_to_int[src]].insert(name_to_int[v[j]]);
        }
    }
    vector<int> dist(cities, 2e9), parent(cities, -1), ans;
    cin >> start >> end;
    if (name_to_int.count(start) == 0 || name_to_int.count(end) == 0) {
        cout << "no route found";
        return 0;
    }
    start_int = name_to_int[start];
    end_int = name_to_int[end];

    dist[start_int] = 0;
    q.push(start_int);
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        for (auto& v : AL[curr]) {
            if (dist[v] != 2e9) continue;
            parent[v] = curr;
            dist[v] = dist[curr] + 1;
            q.push(v);
        }
    }
    if (dist[end_int] == 2e9) cout << "no route found";
    else {
        int curr = end_int;
        while (curr != -1) {
            ans.push_back(curr);
            curr = parent[curr];
        }
        reverse(ans.begin(), ans.end());
        for (int i : ans) cout << int_to_name[i] << ' ';
    }
}
