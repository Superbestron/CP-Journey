#include <bits/stdc++.h>

using namespace std;

int AM[500][500], p[500][500];
vector<int> ans;

vector<string> split(string& s, string&& delimiter) {
    size_t pos;
    string token;
    vector<string> arr;
    if (s.empty()) return arr;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        arr.emplace_back(token);
        s.erase(0, pos + delimiter.size());
    }
    arr.emplace_back(s);
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<string, int> name_to_int;
    unordered_map<int, string> int_to_name;
    int n, k; cin >> n;
    string name, temp;
    for (int u = 0; u < n; ++u) {
        cin >> name;
        name_to_int[name] = u;
        int_to_name[u] = name;
    }
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            AM[u][v] = 1e9;
            p[u][v] = u;
        }
    }
    for (int u = 0; u < n; ++u) {
        cin >> name >> k;
        int v = name_to_int[name];
        for (int i = 0; i < k; i++) {
            cin >> temp; cin.ignore();
            getline(cin, temp);

            vector<string> vect = split(temp, ", ");
            for (string& u_str : vect) {
                AM[name_to_int[u_str]][v] = 1;
            }
        }
    }
    for (int a = 0; a < n; a++)                    // loop order is k->u->v
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) {
                if (AM[u][a] + AM[a][v] < AM[u][v]) {
                    AM[u][v] = AM[u][a] + AM[a][v];
                    p[u][v] = p[a][v];
                }
            }
    int min = 1e9, min_cycle_index = 1e9;
    for (int i = 0; i < n; i++) {
        if (AM[i][i] < min) {
            ans.clear();
            min = AM[i][i];
            min_cycle_index = i;
        }
    }
    if (min_cycle_index == 1e9) {
        cout << "SHIP IT";
        return 0;
    }

    int cur_node = p[min_cycle_index][min_cycle_index];
    while (cur_node != min_cycle_index){
        ans.push_back(cur_node);
        cur_node = p[min_cycle_index][cur_node];
    }
    ans.emplace_back(min_cycle_index);
    for (int u : ans) {
        cout << int_to_name[u] << ' ';
    }
}